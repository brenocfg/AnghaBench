#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct super_block {int dummy; } ;
struct page {int index; TYPE_1__* mapping; } ;
struct inode {int i_ino; struct super_block* i_sb; } ;
struct hfs_btree {scalar_t__ node_size; int node_size_shift; int node_count; int /*<<< orphan*/  hash_lock; } ;
struct hfs_bnode {int /*<<< orphan*/  refcnt; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_4__ {struct hfs_btree* attr_tree; struct hfs_btree* cat_tree; struct hfs_btree* ext_tree; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  HFSPLUS_ATTR_CNID 130 
#define  HFSPLUS_CAT_CNID 129 
#define  HFSPLUS_EXT_CNID 128 
 TYPE_2__ HFSPLUS_SB (struct super_block*) ; 
 int PAGE_CACHE_SHIFT ; 
 scalar_t__ PAGE_CACHE_SIZE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct hfs_bnode* hfs_bnode_findhash (struct hfs_btree*,int) ; 
 int /*<<< orphan*/  hfs_bnode_free (struct hfs_bnode*) ; 
 int /*<<< orphan*/  hfs_bnode_unhash (struct hfs_bnode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int try_to_free_buffers (struct page*) ; 

__attribute__((used)) static int hfsplus_releasepage(struct page *page, gfp_t mask)
{
	struct inode *inode = page->mapping->host;
	struct super_block *sb = inode->i_sb;
	struct hfs_btree *tree;
	struct hfs_bnode *node;
	u32 nidx;
	int i, res = 1;

	switch (inode->i_ino) {
	case HFSPLUS_EXT_CNID:
		tree = HFSPLUS_SB(sb).ext_tree;
		break;
	case HFSPLUS_CAT_CNID:
		tree = HFSPLUS_SB(sb).cat_tree;
		break;
	case HFSPLUS_ATTR_CNID:
		tree = HFSPLUS_SB(sb).attr_tree;
		break;
	default:
		BUG();
		return 0;
	}
	if (!tree)
		return 0;
	if (tree->node_size >= PAGE_CACHE_SIZE) {
		nidx = page->index >> (tree->node_size_shift - PAGE_CACHE_SHIFT);
		spin_lock(&tree->hash_lock);
		node = hfs_bnode_findhash(tree, nidx);
		if (!node)
			;
		else if (atomic_read(&node->refcnt))
			res = 0;
		if (res && node) {
			hfs_bnode_unhash(node);
			hfs_bnode_free(node);
		}
		spin_unlock(&tree->hash_lock);
	} else {
		nidx = page->index << (PAGE_CACHE_SHIFT - tree->node_size_shift);
		i = 1 << (PAGE_CACHE_SHIFT - tree->node_size_shift);
		spin_lock(&tree->hash_lock);
		do {
			node = hfs_bnode_findhash(tree, nidx++);
			if (!node)
				continue;
			if (atomic_read(&node->refcnt)) {
				res = 0;
				break;
			}
			hfs_bnode_unhash(node);
			hfs_bnode_free(node);
		} while (--i && nidx < tree->node_count);
		spin_unlock(&tree->hash_lock);
	}
	return res ? try_to_free_buffers(page) : 0;
}