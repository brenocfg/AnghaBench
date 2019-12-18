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
struct mmu_notifier {int /*<<< orphan*/  hlist; TYPE_1__* ops; } ;
struct mm_struct {int /*<<< orphan*/  mm_count; TYPE_2__* mmu_notifier_mm; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* release ) (struct mmu_notifier*,struct mm_struct*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_del_init_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_unhashed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmdrop (struct mm_struct*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (struct mmu_notifier*,struct mm_struct*) ; 
 int /*<<< orphan*/  synchronize_srcu (int /*<<< orphan*/ *) ; 

void mmu_notifier_unregister(struct mmu_notifier *mn, struct mm_struct *mm)
{
	BUG_ON(atomic_read(&mm->mm_count) <= 0);

	if (!hlist_unhashed(&mn->hlist)) {
		/*
		 * SRCU here will force exit_mmap to wait ->release to finish
		 * before freeing the pages.
		 */
		int id;

		id = srcu_read_lock(&srcu);
		/*
		 * exit_mmap will block in mmu_notifier_release to
		 * guarantee ->release is called before freeing the
		 * pages.
		 */
		if (mn->ops->release)
			mn->ops->release(mn, mm);
		srcu_read_unlock(&srcu, id);

		spin_lock(&mm->mmu_notifier_mm->lock);
		/*
		 * Can not use list_del_rcu() since __mmu_notifier_release
		 * can delete it before we hold the lock.
		 */
		hlist_del_init_rcu(&mn->hlist);
		spin_unlock(&mm->mmu_notifier_mm->lock);
	}

	/*
	 * Wait any running method to finish, of course including
	 * ->release if it was run by mmu_notifier_relase instead of us.
	 */
	synchronize_srcu(&srcu);

	BUG_ON(atomic_read(&mm->mm_count) <= 0);

	mmdrop(mm);
}