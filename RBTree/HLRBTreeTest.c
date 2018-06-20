//
//  HLRBTreeTest.c
//  HalleyAliveSDKTestDemo
//
//  Created by acewu on 21/09/2017.
//  Copyright © 2017 Tencent. All rights reserved.
//

#include "HLRBTreeTest.h"
#include "HLRBTree.h"
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

typedef struct HLTestRBTree {
	struct rb_node node;
	
	uint64_t tag;

} HLTestRBTree;


// session 中 sessionProcess 索引 -- sessionProcessTree
static signed int test_compare_nodes(void *ctx, const void *n1, const void *n2) {
	const HLTestRBTree *t1 = n1;
	const HLTestRBTree *t2 = n2;
	
	if (t1->tag > t2->tag) {
		return 1;
	}else if (t1->tag < t2->tag) {
		return -1;
	}
	
	return 0;
}
static signed int test_compare_key(void *ctx, const void *n1, const void *keyp) {
	const HLTestRBTree *t1 = n1;
	const uint64_t tag = *((uint64_t *)keyp);
	if (t1->tag > tag) {
		return 1;
	}else if (t1->tag < tag) {
		return -1;
	}
	return 0;
}

int apiHLTestRbtree() {
	rb_tree_t tree;
	// 2. 链表初始化
	static const rb_tree_ops_t session_process_id_tree_ops = {
		.rbto_compare_nodes = test_compare_nodes,
		.rbto_compare_key = test_compare_key,
		.rbto_node_offset = offsetof(HLTestRBTree, node),
	};
	rb_tree_init(&tree, &session_process_id_tree_ops);
	
	int64_t i = 0;
	int64_t max = 10000;
	for (i = 0; i < max; i+=3) {
		HLTestRBTree *item = calloc(sizeof(HLTestRBTree), 1);
		item->tag = i;
		assert(rb_tree_find_node(&tree, &i) == NULL);
		rb_tree_insert_node(&tree, item);
	}
	for (i = 0; i < max; i+=3) {
		HLTestRBTree *item = rb_tree_find_node(&tree, &i);
		assert(item != NULL);
		rb_tree_remove_node(&tree, item);
		assert(rb_tree_find_node(&tree, &i) == NULL);
		free(item);
	}
	for (i = 0; i < max; i+=3) {
		HLTestRBTree *item = calloc(sizeof(HLTestRBTree), 1);
		item->tag = i;
		assert(rb_tree_find_node(&tree, &i) == NULL);
		rb_tree_insert_node(&tree, item);
	}
	for (i = 1; i < max; i+=3) {
		HLTestRBTree *item = calloc(sizeof(HLTestRBTree), 1);
		item->tag = i;
		assert(rb_tree_find_node(&tree, &i) == NULL);
		rb_tree_insert_node(&tree, item);
	}
	for (i = 2; i < max; i+=3) {
		HLTestRBTree *item = calloc(sizeof(HLTestRBTree), 1);
		item->tag = i;
		assert(rb_tree_find_node(&tree, &i) == NULL);
		rb_tree_insert_node(&tree, item);
	}
	
	assert(rb_tree_count(&tree) == max);
	for (i = 1; i < max; i+=3) {
		HLTestRBTree *item = rb_tree_find_node(&tree, &i);
		assert(item != NULL);
		rb_tree_remove_node(&tree, item);
		assert(rb_tree_find_node(&tree, &i) == NULL);
		free(item);
	}
	for (i = 1; i < max; i+=3) {
		HLTestRBTree *item = calloc(sizeof(HLTestRBTree), 1);
		item->tag = i;
		assert(rb_tree_find_node(&tree, &i) == NULL);
		rb_tree_insert_node(&tree, item);
	}
	assert(rb_tree_count(&tree) == max);
	for (i = 0; i < max; i++) {
		HLTestRBTree *item = rb_tree_find_node(&tree, &i);
		assert(item != NULL);
		rb_tree_remove_node(&tree, item);
		assert(rb_tree_find_node(&tree, &i) == NULL);
		free(item);
	}
	assert(rb_tree_count(&tree) == 0);
	return 0;
}

