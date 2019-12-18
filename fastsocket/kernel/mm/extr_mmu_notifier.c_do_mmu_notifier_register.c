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
struct mmu_notifier_mm {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct mmu_notifier {int /*<<< orphan*/  hlist; } ;
struct mm_struct {int /*<<< orphan*/  mm_users; int /*<<< orphan*/  mmap_sem; struct mmu_notifier_mm* mmu_notifier_mm; int /*<<< orphan*/  mm_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  per_cpu_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mmu_notifier_mm*) ; 
 struct mmu_notifier_mm* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mm_drop_all_locks (struct mm_struct*) ; 
 int /*<<< orphan*/  mm_has_notifiers (struct mm_struct*) ; 
 int mm_take_all_locks (struct mm_struct*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ srcu ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_mmu_notifier_register(struct mmu_notifier *mn,
				    struct mm_struct *mm,
				    int take_mmap_sem)
{
	struct mmu_notifier_mm *mmu_notifier_mm;
	int ret;

	BUG_ON(atomic_read(&mm->mm_users) <= 0);

	/*
	* Verify that mmu_notifier_init() already run and the global srcu is
	* initialized.
	*/
	BUG_ON(!srcu.per_cpu_ref);

	ret = -ENOMEM;
	mmu_notifier_mm = kmalloc(sizeof(struct mmu_notifier_mm), GFP_KERNEL);
	if (unlikely(!mmu_notifier_mm))
		goto out;

	if (take_mmap_sem)
		down_write(&mm->mmap_sem);
	ret = mm_take_all_locks(mm);
	if (unlikely(ret))
		goto out_cleanup;

	if (!mm_has_notifiers(mm)) {
		INIT_HLIST_HEAD(&mmu_notifier_mm->list);
		spin_lock_init(&mmu_notifier_mm->lock);
		mm->mmu_notifier_mm = mmu_notifier_mm;
		mmu_notifier_mm = NULL;
	}
	atomic_inc(&mm->mm_count);

	/*
	 * Serialize the update against mmu_notifier_unregister. A
	 * side note: mmu_notifier_release can't run concurrently with
	 * us because we hold the mm_users pin (either implicitly as
	 * current->mm or explicitly with get_task_mm() or similar).
	 * We can't race against any other mmu notifier method either
	 * thanks to mm_take_all_locks().
	 */
	spin_lock(&mm->mmu_notifier_mm->lock);
	hlist_add_head(&mn->hlist, &mm->mmu_notifier_mm->list);
	spin_unlock(&mm->mmu_notifier_mm->lock);

	mm_drop_all_locks(mm);
out_cleanup:
	if (take_mmap_sem)
		up_write(&mm->mmap_sem);
	/* kfree() does nothing if mmu_notifier_mm is NULL */
	kfree(mmu_notifier_mm);
out:
	BUG_ON(atomic_read(&mm->mm_users) <= 0);
	return ret;
}