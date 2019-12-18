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
struct utrace {int /*<<< orphan*/  resume; int /*<<< orphan*/  attaching; int /*<<< orphan*/  attached; int /*<<< orphan*/  lock; } ;
struct task_struct {struct utrace* utrace; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UTRACE_RESUME ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct utrace*) ; 
 struct utrace* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  utrace_cachep ; 

__attribute__((used)) static bool utrace_task_alloc(struct task_struct *task)
{
	struct utrace *utrace = kmem_cache_zalloc(utrace_cachep, GFP_KERNEL);
	if (unlikely(!utrace))
		return false;
	spin_lock_init(&utrace->lock);
	INIT_LIST_HEAD(&utrace->attached);
	INIT_LIST_HEAD(&utrace->attaching);
	utrace->resume = UTRACE_RESUME;
	task_lock(task);
	if (likely(!task->utrace)) {
		/*
		 * This barrier makes sure the initialization of the struct
		 * precedes the installation of the pointer.  This pairs
		 * with smp_read_barrier_depends() in task_utrace_struct().
		 */
		smp_wmb();
		task->utrace = utrace;
	}
	task_unlock(task);

	if (unlikely(task->utrace != utrace))
		kmem_cache_free(utrace_cachep, utrace);
	return true;
}