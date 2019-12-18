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
struct ubifs_znode {int child_cnt; scalar_t__ level; TYPE_1__* zbranch; } ;
struct TYPE_2__ {struct ubifs_znode* znode; } ;

/* Variables and functions */
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  kfree (struct ubifs_znode*) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_znode*) ; 
 struct ubifs_znode* ubifs_tnc_postorder_first (struct ubifs_znode*) ; 
 struct ubifs_znode* ubifs_tnc_postorder_next (struct ubifs_znode*) ; 
 int /*<<< orphan*/  ubifs_zn_dirty (struct ubifs_znode*) ; 

long ubifs_destroy_tnc_subtree(struct ubifs_znode *znode)
{
	struct ubifs_znode *zn = ubifs_tnc_postorder_first(znode);
	long clean_freed = 0;
	int n;

	ubifs_assert(zn);
	while (1) {
		for (n = 0; n < zn->child_cnt; n++) {
			if (!zn->zbranch[n].znode)
				continue;

			if (zn->level > 0 &&
			    !ubifs_zn_dirty(zn->zbranch[n].znode))
				clean_freed += 1;

			cond_resched();
			kfree(zn->zbranch[n].znode);
		}

		if (zn == znode) {
			if (!ubifs_zn_dirty(zn))
				clean_freed += 1;
			kfree(zn);
			return clean_freed;
		}

		zn = ubifs_tnc_postorder_next(zn);
	}
}