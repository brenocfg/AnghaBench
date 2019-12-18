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
typedef  int /*<<< orphan*/  thread_t ;
typedef  int /*<<< orphan*/  thread_continue_t ;
typedef  int /*<<< orphan*/  task_t ;
struct thread_exception_elt {int /*<<< orphan*/  exception_thread; int /*<<< orphan*/  exception_task; int /*<<< orphan*/  exception_type; } ;
typedef  int /*<<< orphan*/  exception_type_t ;
typedef  int /*<<< orphan*/  event_t ;

/* Variables and functions */
 int /*<<< orphan*/  THREAD_UNINT ; 
 int /*<<< orphan*/  assert_thread_magic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dequeue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct thread_exception_elt*,int) ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_deallocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_deliver_crash_notification (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_wait_till_threads_terminate_locked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_deallocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_exception_lock ; 
 int /*<<< orphan*/  thread_exception_queue ; 

__attribute__((used)) static void
thread_exception_daemon(void)
{
	struct thread_exception_elt *elt;
	task_t task;
	thread_t thread;
	exception_type_t etype;

	simple_lock(&thread_exception_lock);
	while ((elt = (struct thread_exception_elt *)dequeue_head(&thread_exception_queue)) != NULL) {
		simple_unlock(&thread_exception_lock);

		etype = elt->exception_type;
		task = elt->exception_task;
		thread = elt->exception_thread;
		assert_thread_magic(thread);

		kfree(elt, sizeof (*elt));

		/* wait for all the threads in the task to terminate */
		task_lock(task);
		task_wait_till_threads_terminate_locked(task);
		task_unlock(task);

		/* Consumes the task ref returned by task_generate_corpse_internal */
		task_deallocate(task);
		/* Consumes the thread ref returned by task_generate_corpse_internal */
		thread_deallocate(thread);

		/* Deliver the notification, also clears the corpse. */
		task_deliver_crash_notification(task, thread, etype, 0);

		simple_lock(&thread_exception_lock);
	}

	assert_wait((event_t)&thread_exception_queue, THREAD_UNINT);
	simple_unlock(&thread_exception_lock);

	thread_block((thread_continue_t)thread_exception_daemon);
}