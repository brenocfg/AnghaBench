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
struct ubifs_znode {int child_cnt; int alt; struct ubifs_zbranch* zbranch; scalar_t__ level; } ;
struct ubifs_zbranch {TYPE_1__* znode; } ;
struct TYPE_2__ {int iip; } ;

/* Variables and functions */
 int /*<<< orphan*/  ubifs_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_zn_dirty (struct ubifs_znode*) ; 

__attribute__((used)) static void insert_zbranch(struct ubifs_znode *znode,
			   const struct ubifs_zbranch *zbr, int n)
{
	int i;

	ubifs_assert(ubifs_zn_dirty(znode));

	if (znode->level) {
		for (i = znode->child_cnt; i > n; i--) {
			znode->zbranch[i] = znode->zbranch[i - 1];
			if (znode->zbranch[i].znode)
				znode->zbranch[i].znode->iip = i;
		}
		if (zbr->znode)
			zbr->znode->iip = n;
	} else
		for (i = znode->child_cnt; i > n; i--)
			znode->zbranch[i] = znode->zbranch[i - 1];

	znode->zbranch[n] = *zbr;
	znode->child_cnt += 1;

	/*
	 * After inserting at slot zero, the lower bound of the key range of
	 * this znode may have changed. If this znode is subsequently split
	 * then the upper bound of the key range may change, and furthermore
	 * it could change to be lower than the original lower bound. If that
	 * happens, then it will no longer be possible to find this znode in the
	 * TNC using the key from the index node on flash. That is bad because
	 * if it is not found, we will assume it is obsolete and may overwrite
	 * it. Then if there is an unclean unmount, we will start using the
	 * old index which will be broken.
	 *
	 * So we first mark znodes that have insertions at slot zero, and then
	 * if they are split we add their lnum/offs to the old_idx tree.
	 */
	if (n == 0)
		znode->alt = 1;
}