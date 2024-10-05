//Cartesian Tree Structure is a binary tree derived from an array where:
// The root of the tree is the minimum element of the array.
// The left subtree is constructed from elements before the minimum element.
// The right subtree is constructed from elements after the minimum element.

// Time Complexity: O(n) and Space Complexity: O(n)

#include <iostream>
#include <vector>
#include <stack>

class CartesianTree {
private:
    struct Node {
        int value;
        int index;
        Node* left;
        Node* right;
        Node(int v, int i) : value(v), index(i), left(nullptr), right(nullptr) {}
    };

    Node* root;

public:
    CartesianTree(const std::vector<int>& arr) {
        root = buildCartesianTree(arr);
    }

    ~CartesianTree() {
        destroyTree(root);
    }

    Node* buildCartesianTree(const std::vector<int>& arr) {
        if (arr.empty()) return nullptr;

        std::stack<Node*> stack;
        Node* root = nullptr;

        for (int i = 0; i < arr.size(); ++i) {
            Node* last = nullptr;
            Node* node = new Node(arr[i], i);

            while (!stack.empty() && stack.top()->value > arr[i]) {
                last = stack.top();
                stack.pop();
            }

            if (!stack.empty()) {
                stack.top()->right = node;
            } else {
                root = node;
            }

            node->left = last;
            stack.push(node);
        }

        return root;
    }

    void destroyTree(Node* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    // Utility function to print the tree (in-order traversal)
    void printTree() {
        std::cout << "Cartesian Tree (in-order traversal):" << std::endl;
        printTreeHelper(root);
        std::cout << std::endl;
    }

private:
    void printTreeHelper(Node* node) {
        if (node) {
            printTreeHelper(node->left);
            std::cout << "(" << node->value << ", " << node->index << ") ";
            printTreeHelper(node->right);
        }
    }

public:
    // Range Minimum Query (RMQ) implementation
    int rangeMinimumQuery(int left, int right) {
        return rmqHelper(root, left, right);
    }

private:
    int rmqHelper(Node* node, int left, int right) {
        if (!node || node->index < left || node->index > right) {
            return INT_MAX;
        }

        if (left <= node->index && node->index <= right) {
            int leftMin = rmqHelper(node->left, left, right);
            int rightMin = rmqHelper(node->right, left, right);
            return std::min({node->value, leftMin, rightMin});
        }

        if (node->index > right) {
            return rmqHelper(node->left, left, right);
        }

        return rmqHelper(node->right, left, right);
    }
};

int main() {
    std::vector<int> arr = {9, 3, 7, 1, 8, 12, 10, 20, 15, 18, 5};
    CartesianTree ct(arr);

    std::cout << "Original array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    ct.printTree();

    // Demonstrate Range Minimum Query
    int left = 2, right = 8;
    int minInRange = ct.rangeMinimumQuery(left, right);
    std::cout << "Minimum value in range [" << left << ", " << right << "]: " << minInRange << std::endl;

    return 0;
}
