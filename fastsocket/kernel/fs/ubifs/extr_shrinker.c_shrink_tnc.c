#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ubifs_znode {size_t iip; TYPE_2__* parent; scalar_t__ time; scalar_t__ cnext; } ;
struct TYPE_6__ {int /*<<< orphan*/ * znode; } ;
struct ubifs_info {TYPE_3__ zroot; int /*<<< orphan*/  clean_zn_cnt; int /*<<< orphan*/  tnc_mutex; int /*<<< orphan*/  umount_mutex; } ;
struct TYPE_5__ {TYPE_1__* zbranch; } ;
struct TYPE_4__ {int /*<<< orphan*/ * znode; } ;

/* Variables and functions */
 int abs (scalar_t__) ; 
 scalar_t__ atomic_long_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_sub (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int get_seconds () ; 
 int mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_assert (int) ; 
 int /*<<< orphan*/  ubifs_clean_zn_cnt ; 
 int ubifs_destroy_tnc_subtree (struct ubifs_znode*) ; 
 struct ubifs_znode* ubifs_tnc_levelorder_next (int /*<<< orphan*/ *,struct ubifs_znode*) ; 
 int /*<<< orphan*/  ubifs_zn_dirty (struct ubifs_znode*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int shrink_tnc(struct ubifs_info *c, int nr, int age, int *contention)
{
	int total_freed = 0;
	struct ubifs_znode *znode, *zprev;
	int time = get_seconds();

	ubifs_assert(mutex_is_locked(&c->umount_mutex));
	ubifs_assert(mutex_is_locked(&c->tnc_mutex));

	if (!c->zroot.znode || atomic_long_read(&c->clean_zn_cnt) == 0)
		return 0;

	/*
	 * Traverse the TNC tree in levelorder manner, so that it is possible
	 * to destroy large sub-trees. Indeed, if a znode is old, then all its
	 * children are older or of the same age.
	 *
	 * Note, we are holding 'c->tnc_mutex', so we do not have to lock the
	 * 'c->space_lock' when _reading_ 'c->clean_zn_cnt', because it is
	 * changed only when the 'c->tnc_mutex' is held.
	 */
	zprev = NULL;
	znode = ubifs_tnc_levelorder_next(c->zroot.znode, NULL);
	while (znode && total_freed < nr &&
	       atomic_long_read(&c->clean_zn_cnt) > 0) {
		int freed;

		/*
		 * If the znode is clean, but it is in the 'c->cnext' list, this
		 * means that this znode has just been written to flash as a
		 * part of commit and was marked clean. They will be removed
		 * from the list at end commit. We cannot change the list,
		 * because it is not protected by any mutex (design decision to
		 * make commit really independent and parallel to main I/O). So
		 * we just skip these znodes.
		 *
		 * Note, the 'clean_zn_cnt' counters are not updated until
		 * after the commit, so the UBIFS shrinker does not report
		 * the znodes which are in the 'c->cnext' list as freeable.
		 *
		 * Also note, if the root of a sub-tree is not in 'c->cnext',
		 * then the whole sub-tree is not in 'c->cnext' as well, so it
		 * is safe to dump whole sub-tree.
		 */

		if (znode->cnext) {
			/*
			 * Very soon these znodes will be removed from the list
			 * and become freeable.
			 */
			*contention = 1;
		} else if (!ubifs_zn_dirty(znode) &&
			   abs(time - znode->time) >= age) {
			if (znode->parent)
				znode->parent->zbranch[znode->iip].znode = NULL;
			else
				c->zroot.znode = NULL;

			freed = ubifs_destroy_tnc_subtree(znode);
			atomic_long_sub(freed, &ubifs_clean_zn_cnt);
			atomic_long_sub(freed, &c->clean_zn_cnt);
			ubifs_assert(atomic_long_read(&c->clean_zn_cnt) >= 0);
			total_freed += freed;
			znode = zprev;
		}

		if (unlikely(!c->zroot.znode))
			break;

		zprev = znode;
		znode = ubifs_tnc_levelorder_next(c->zroot.znode, znode);
		cond_resched();
	}

	return total_freed;
}