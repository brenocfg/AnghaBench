#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct page {int dummy; } ;
struct hfs_btree_header_rec {int /*<<< orphan*/  depth; void* attributes; void* free_nodes; void* node_count; void* leaf_tail; void* leaf_head; void* leaf_count; void* root; } ;
struct hfs_btree {int /*<<< orphan*/  depth; int /*<<< orphan*/  attributes; int /*<<< orphan*/  free_nodes; int /*<<< orphan*/  node_count; int /*<<< orphan*/  leaf_tail; int /*<<< orphan*/  leaf_head; int /*<<< orphan*/  leaf_count; int /*<<< orphan*/  root; } ;
struct hfs_bnode_desc {int dummy; } ;
struct hfs_bnode {struct page** page; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct hfs_bnode*) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 struct hfs_bnode* hfs_bnode_find (struct hfs_btree*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfs_bnode_put (struct hfs_bnode*) ; 
 scalar_t__ kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 

void hfs_btree_write(struct hfs_btree *tree)
{
	struct hfs_btree_header_rec *head;
	struct hfs_bnode *node;
	struct page *page;

	node = hfs_bnode_find(tree, 0);
	if (IS_ERR(node))
		/* panic? */
		return;
	/* Load the header */
	page = node->page[0];
	head = (struct hfs_btree_header_rec *)(kmap(page) + sizeof(struct hfs_bnode_desc));

	head->root = cpu_to_be32(tree->root);
	head->leaf_count = cpu_to_be32(tree->leaf_count);
	head->leaf_head = cpu_to_be32(tree->leaf_head);
	head->leaf_tail = cpu_to_be32(tree->leaf_tail);
	head->node_count = cpu_to_be32(tree->node_count);
	head->free_nodes = cpu_to_be32(tree->free_nodes);
	head->attributes = cpu_to_be32(tree->attributes);
	head->depth = cpu_to_be16(tree->depth);

	kunmap(page);
	set_page_dirty(page);
	hfs_bnode_put(node);
}