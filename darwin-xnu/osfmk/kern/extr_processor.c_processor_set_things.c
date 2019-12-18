#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_size_t ;
typedef  TYPE_1__* thread_t ;
typedef  TYPE_2__* task_t ;
typedef  int /*<<< orphan*/  queue_entry_t ;
typedef  int /*<<< orphan*/ * processor_set_t ;
typedef  unsigned int mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_10__ {int /*<<< orphan*/  tasks; } ;
struct TYPE_9__ {TYPE_2__* task; int /*<<< orphan*/  threads; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_RESOURCE_SHORTAGE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/ * PROCESSOR_SET_NULL ; 
 int PSET_THING_THREAD ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bcopy (void*,void*,int) ; 
 void* kalloc (int) ; 
 TYPE_2__* kernel_task ; 
 int /*<<< orphan*/  kfree (void*,int) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ mac_task_check_expose_task (TYPE_2__*) ; 
 int /*<<< orphan*/  pset0 ; 
 int /*<<< orphan*/  queue_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ queue_first (int /*<<< orphan*/ *) ; 
 scalar_t__ queue_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_deallocate (TYPE_2__*) ; 
 int /*<<< orphan*/  task_reference_internal (TYPE_2__*) ; 
 int /*<<< orphan*/  tasks ; 
 int tasks_count ; 
 int /*<<< orphan*/  tasks_threads_lock ; 
 int /*<<< orphan*/  thread_deallocate (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_reference_internal (TYPE_1__*) ; 
 int /*<<< orphan*/  threads ; 
 int threads_count ; 

kern_return_t
processor_set_things(
	processor_set_t	pset,
	void **thing_list,
	mach_msg_type_number_t *count,
	int type)
{
	unsigned int i;
	task_t task;
	thread_t thread;

	task_t *task_list;
	unsigned int actual_tasks;
	vm_size_t task_size, task_size_needed;

	thread_t *thread_list;
	unsigned int actual_threads;
	vm_size_t thread_size, thread_size_needed;

	void *addr, *newaddr;
	vm_size_t size, size_needed;

	if (pset == PROCESSOR_SET_NULL || pset != &pset0)
		return (KERN_INVALID_ARGUMENT);

	task_size = 0;
	task_size_needed = 0;
	task_list = NULL;
	actual_tasks = 0;

	thread_size = 0;
	thread_size_needed = 0;
	thread_list = NULL;
	actual_threads = 0;

	for (;;) {
		lck_mtx_lock(&tasks_threads_lock);

		/* do we have the memory we need? */
		if (type == PSET_THING_THREAD)
			thread_size_needed = threads_count * sizeof(void *);
#if !CONFIG_MACF
		else
#endif
			task_size_needed = tasks_count * sizeof(void *);

		if (task_size_needed <= task_size &&
		    thread_size_needed <= thread_size)
			break;

		/* unlock and allocate more memory */
		lck_mtx_unlock(&tasks_threads_lock);

		/* grow task array */
		if (task_size_needed > task_size) {
			if (task_size != 0)
				kfree(task_list, task_size);

			assert(task_size_needed > 0);
			task_size = task_size_needed;

			task_list = (task_t *)kalloc(task_size);
			if (task_list == NULL) {
				if (thread_size != 0)
					kfree(thread_list, thread_size);
				return (KERN_RESOURCE_SHORTAGE);
			}
		}

		/* grow thread array */
		if (thread_size_needed > thread_size) {
			if (thread_size != 0)
				kfree(thread_list, thread_size);

			assert(thread_size_needed > 0);
			thread_size = thread_size_needed;

			thread_list = (thread_t *)kalloc(thread_size);
			if (thread_list == 0) {
				if (task_size != 0)
					kfree(task_list, task_size);
				return (KERN_RESOURCE_SHORTAGE);
			}
		}
	}

	/* OK, have memory and the list locked */

	/* If we need it, get the thread list */
	if (type == PSET_THING_THREAD) {
		for (thread = (thread_t)queue_first(&threads);
		     !queue_end(&threads, (queue_entry_t)thread);
		     thread = (thread_t)queue_next(&thread->threads)) {
#if defined(SECURE_KERNEL)
			if (thread->task != kernel_task) {
#endif
				thread_reference_internal(thread);
				thread_list[actual_threads++] = thread;
#if defined(SECURE_KERNEL)
			}
#endif
		}
	}
#if !CONFIG_MACF
	  else {
#endif
		/* get a list of the tasks */
		for (task = (task_t)queue_first(&tasks);
		     !queue_end(&tasks, (queue_entry_t)task);
		     task = (task_t)queue_next(&task->tasks)) {
#if defined(SECURE_KERNEL)
			if (task != kernel_task) {
#endif
				task_reference_internal(task);
				task_list[actual_tasks++] = task;
#if defined(SECURE_KERNEL)
			}
#endif
		}
#if !CONFIG_MACF
	}
#endif

	lck_mtx_unlock(&tasks_threads_lock);

#if CONFIG_MACF
	unsigned int j, used;

	/* for each task, make sure we are allowed to examine it */
	for (i = used = 0; i < actual_tasks; i++) {
		if (mac_task_check_expose_task(task_list[i])) {
			task_deallocate(task_list[i]);
			continue;
		}
		task_list[used++] = task_list[i];
	}
	actual_tasks = used;
	task_size_needed = actual_tasks * sizeof(void *);

	if (type == PSET_THING_THREAD) {

		/* for each thread (if any), make sure it's task is in the allowed list */
		for (i = used = 0; i < actual_threads; i++) {
			boolean_t found_task = FALSE;

			task = thread_list[i]->task;
			for (j = 0; j < actual_tasks; j++) {
				if (task_list[j] == task) {
					found_task = TRUE;
					break;
				}
			}
			if (found_task)
				thread_list[used++] = thread_list[i];
			else
				thread_deallocate(thread_list[i]);
		}
		actual_threads = used;
		thread_size_needed = actual_threads * sizeof(void *);

		/* done with the task list */
		for (i = 0; i < actual_tasks; i++)
			task_deallocate(task_list[i]);
		kfree(task_list, task_size);
		task_size = 0;
		actual_tasks = 0;
		task_list = NULL;
	}
#endif

	if (type == PSET_THING_THREAD) {
		if (actual_threads == 0) {
			/* no threads available to return */
			assert(task_size == 0);
			if (thread_size != 0)
				kfree(thread_list, thread_size);
			*thing_list = NULL;
			*count = 0;
			return KERN_SUCCESS;
		}
		size_needed = actual_threads * sizeof(void *);
		size = thread_size;
		addr = thread_list;
	} else {
		if (actual_tasks == 0) {
			/* no tasks available to return */
			assert(thread_size == 0);
			if (task_size != 0)
				kfree(task_list, task_size);
			*thing_list = NULL;
			*count = 0;
			return KERN_SUCCESS;
		} 
		size_needed = actual_tasks * sizeof(void *);
		size = task_size;
		addr = task_list;
	}

	/* if we allocated too much, must copy */
	if (size_needed < size) {
		newaddr = kalloc(size_needed);
		if (newaddr == 0) {
			for (i = 0; i < actual_tasks; i++) {
				if (type == PSET_THING_THREAD)
					thread_deallocate(thread_list[i]);
				else
					task_deallocate(task_list[i]);
			}
			if (size)
				kfree(addr, size);
			return (KERN_RESOURCE_SHORTAGE);
		}

		bcopy((void *) addr, (void *) newaddr, size_needed);
		kfree(addr, size);

		addr = newaddr;
		size = size_needed;
	}

	*thing_list = (void **)addr;
	*count = (unsigned int)size / sizeof(void *);

	return (KERN_SUCCESS);
}