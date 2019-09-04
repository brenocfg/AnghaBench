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
typedef  int /*<<< orphan*/  task_t ;
struct thread_exception_elt {int /*<<< orphan*/  exception_thread; int /*<<< orphan*/  exception_task; scalar_t__ exception_type; } ;
typedef  int /*<<< orphan*/  queue_entry_t ;
typedef  scalar_t__ exception_type_t ;
typedef  int /*<<< orphan*/  event_t ;

/* Variables and functions */
 scalar_t__ EXC_GUARD ; 
 scalar_t__ EXC_RESOURCE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  enqueue_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct thread_exception_elt* kalloc (int) ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_exception_lock ; 
 int /*<<< orphan*/  thread_exception_queue ; 
 int /*<<< orphan*/  thread_wakeup (int /*<<< orphan*/ ) ; 

void
thread_exception_enqueue(
	task_t		task,
	thread_t	thread,
	exception_type_t etype)
{
	assert(EXC_RESOURCE == etype || EXC_GUARD == etype);
	struct thread_exception_elt *elt = kalloc(sizeof (*elt));
	elt->exception_type = etype;
	elt->exception_task = task;
	elt->exception_thread = thread;

	simple_lock(&thread_exception_lock);
	enqueue_tail(&thread_exception_queue, (queue_entry_t)elt);
	simple_unlock(&thread_exception_lock);

	thread_wakeup((event_t)&thread_exception_queue);
}