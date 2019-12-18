#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  comm; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int SLOW_WORK_THREAD_LIMIT ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  __clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete_and_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cond_resched () ; 
 TYPE_1__* current ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freezing (TYPE_1__*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait_exclusive (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_freezable () ; 
 int /*<<< orphan*/  set_user_nice (TYPE_1__*,int) ; 
 scalar_t__ slow_work_available (int) ; 
 scalar_t__ slow_work_cull ; 
 scalar_t__ slow_work_cull_thread () ; 
 scalar_t__ slow_work_execute (int) ; 
 int /*<<< orphan*/  slow_work_ids ; 
 int /*<<< orphan*/  slow_work_last_thread_exited ; 
 int slow_work_min_threads ; 
 int /*<<< orphan*/  slow_work_queue ; 
 int /*<<< orphan*/  slow_work_queue_lock ; 
 int /*<<< orphan*/  slow_work_schedule_cull () ; 
 int /*<<< orphan*/  slow_work_set_thread_pid (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slow_work_thread_count ; 
 int /*<<< orphan*/  slow_work_thread_wq ; 
 scalar_t__ slow_work_threads_should_exit ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  try_to_freeze () ; 
 int vslow_work_proportion ; 
 int /*<<< orphan*/  vslow_work_queue ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int slow_work_thread(void *_data)
{
	int vsmax, id;

	DEFINE_WAIT(wait);

	set_freezable();
	set_user_nice(current, -5);

	/* allocate ourselves an ID */
	spin_lock_irq(&slow_work_queue_lock);
	id = find_first_zero_bit(slow_work_ids, SLOW_WORK_THREAD_LIMIT);
	BUG_ON(id < 0 || id >= SLOW_WORK_THREAD_LIMIT);
	__set_bit(id, slow_work_ids);
	slow_work_set_thread_pid(id, current->pid);
	spin_unlock_irq(&slow_work_queue_lock);

	sprintf(current->comm, "kslowd%03u", id);

	for (;;) {
		vsmax = vslow_work_proportion;
		vsmax *= atomic_read(&slow_work_thread_count);
		vsmax /= 100;

		prepare_to_wait_exclusive(&slow_work_thread_wq, &wait,
					  TASK_INTERRUPTIBLE);
		if (!freezing(current) &&
		    !slow_work_threads_should_exit &&
		    !slow_work_available(vsmax) &&
		    !slow_work_cull)
			schedule();
		finish_wait(&slow_work_thread_wq, &wait);

		try_to_freeze();

		vsmax = vslow_work_proportion;
		vsmax *= atomic_read(&slow_work_thread_count);
		vsmax /= 100;

		if (slow_work_available(vsmax) && slow_work_execute(id)) {
			cond_resched();
			if (list_empty(&slow_work_queue) &&
			    list_empty(&vslow_work_queue) &&
			    atomic_read(&slow_work_thread_count) >
			    slow_work_min_threads)
				slow_work_schedule_cull();
			continue;
		}

		if (slow_work_threads_should_exit)
			break;

		if (slow_work_cull && slow_work_cull_thread())
			break;
	}

	spin_lock_irq(&slow_work_queue_lock);
	slow_work_set_thread_pid(id, 0);
	__clear_bit(id, slow_work_ids);
	spin_unlock_irq(&slow_work_queue_lock);

	if (atomic_dec_and_test(&slow_work_thread_count))
		complete_and_exit(&slow_work_last_thread_exited, 0);
	return 0;
}