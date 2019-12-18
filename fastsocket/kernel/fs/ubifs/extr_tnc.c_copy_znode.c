#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ubifs_znode {scalar_t__ level; int child_cnt; struct ubifs_zbranch* zbranch; int /*<<< orphan*/  flags; int /*<<< orphan*/ * cnext; } ;
struct ubifs_zbranch {TYPE_1__* znode; } ;
struct ubifs_info {int /*<<< orphan*/  dirty_zn_cnt; int /*<<< orphan*/  max_znode_sz; } ;
struct TYPE_2__ {struct ubifs_znode* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  COW_ZNODE ; 
 int /*<<< orphan*/  DIRTY_ZNODE ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct ubifs_znode* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  OBSOLETE_ZNODE ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 struct ubifs_znode* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ubifs_znode*,struct ubifs_znode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_assert (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct ubifs_znode *copy_znode(struct ubifs_info *c,
				      struct ubifs_znode *znode)
{
	struct ubifs_znode *zn;

	zn = kmalloc(c->max_znode_sz, GFP_NOFS);
	if (unlikely(!zn))
		return ERR_PTR(-ENOMEM);

	memcpy(zn, znode, c->max_znode_sz);
	zn->cnext = NULL;
	__set_bit(DIRTY_ZNODE, &zn->flags);
	__clear_bit(COW_ZNODE, &zn->flags);

	ubifs_assert(!test_bit(OBSOLETE_ZNODE, &znode->flags));
	__set_bit(OBSOLETE_ZNODE, &znode->flags);

	if (znode->level != 0) {
		int i;
		const int n = zn->child_cnt;

		/* The children now have new parent */
		for (i = 0; i < n; i++) {
			struct ubifs_zbranch *zbr = &zn->zbranch[i];

			if (zbr->znode)
				zbr->znode->parent = zn;
		}
	}

	atomic_long_inc(&c->dirty_zn_cnt);
	return zn;
}