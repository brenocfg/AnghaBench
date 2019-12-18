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
struct ubifs_znode {int child_cnt; int level; int lnum; int offs; int len; size_t iip; int /*<<< orphan*/  flags; struct ubifs_zbranch* zbranch; struct ubifs_znode* parent; } ;
struct ubifs_zbranch {int lnum; int offs; int len; struct ubifs_znode* znode; int /*<<< orphan*/  key; } ;
struct TYPE_4__ {int lnum; int offs; int len; } ;
struct ubifs_info {int /*<<< orphan*/  dirty_zn_cnt; int /*<<< orphan*/  calc_idx_sz; TYPE_2__ zroot; } ;
struct TYPE_3__ {int /*<<< orphan*/  node_type; } ;
struct ubifs_idx_node {void* level; void* child_cnt; TYPE_1__ ch; } ;
struct ubifs_branch {void* len; void* offs; void* lnum; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 scalar_t__ ALIGN (int,int) ; 
 int /*<<< orphan*/  COW_ZNODE ; 
 int /*<<< orphan*/  DIRTY_ZNODE ; 
 int /*<<< orphan*/  UBIFS_IDX_NODE ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_dec (int /*<<< orphan*/ *) ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dbg_dump_znode (struct ubifs_info*,struct ubifs_znode*) ; 
 int insert_old_idx_znode (struct ubifs_info*,struct ubifs_znode*) ; 
 int /*<<< orphan*/  key_write_idx (struct ubifs_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_err (char*) ; 
 struct ubifs_branch* ubifs_idx_branch (struct ubifs_info*,struct ubifs_idx_node*,int) ; 
 int /*<<< orphan*/  ubifs_prepare_node (struct ubifs_info*,struct ubifs_idx_node*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_zn_dirty (struct ubifs_znode*) ; 

__attribute__((used)) static int make_idx_node(struct ubifs_info *c, struct ubifs_idx_node *idx,
			 struct ubifs_znode *znode, int lnum, int offs, int len)
{
	struct ubifs_znode *zp;
	int i, err;

	/* Make index node */
	idx->ch.node_type = UBIFS_IDX_NODE;
	idx->child_cnt = cpu_to_le16(znode->child_cnt);
	idx->level = cpu_to_le16(znode->level);
	for (i = 0; i < znode->child_cnt; i++) {
		struct ubifs_branch *br = ubifs_idx_branch(c, idx, i);
		struct ubifs_zbranch *zbr = &znode->zbranch[i];

		key_write_idx(c, &zbr->key, &br->key);
		br->lnum = cpu_to_le32(zbr->lnum);
		br->offs = cpu_to_le32(zbr->offs);
		br->len = cpu_to_le32(zbr->len);
		if (!zbr->lnum || !zbr->len) {
			ubifs_err("bad ref in znode");
			dbg_dump_znode(c, znode);
			if (zbr->znode)
				dbg_dump_znode(c, zbr->znode);
		}
	}
	ubifs_prepare_node(c, idx, len, 0);

#ifdef CONFIG_UBIFS_FS_DEBUG
	znode->lnum = lnum;
	znode->offs = offs;
	znode->len = len;
#endif

	err = insert_old_idx_znode(c, znode);

	/* Update the parent */
	zp = znode->parent;
	if (zp) {
		struct ubifs_zbranch *zbr;

		zbr = &zp->zbranch[znode->iip];
		zbr->lnum = lnum;
		zbr->offs = offs;
		zbr->len = len;
	} else {
		c->zroot.lnum = lnum;
		c->zroot.offs = offs;
		c->zroot.len = len;
	}
	c->calc_idx_sz += ALIGN(len, 8);

	atomic_long_dec(&c->dirty_zn_cnt);

	ubifs_assert(ubifs_zn_dirty(znode));
	ubifs_assert(test_bit(COW_ZNODE, &znode->flags));

	__clear_bit(DIRTY_ZNODE, &znode->flags);
	__clear_bit(COW_ZNODE, &znode->flags);

	return err;
}