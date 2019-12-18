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
typedef  unsigned int vm_size_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  TYPE_1__* thread_t ;
typedef  int /*<<< orphan*/  queue_entry_t ;
typedef  int /*<<< orphan*/ * processor_set_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_4__ {scalar_t__ kernel_stack; int /*<<< orphan*/  threads; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_NOT_SUPPORTED ; 
 int /*<<< orphan*/  KERN_RESOURCE_SHORTAGE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/ * PROCESSOR_SET_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 void* kalloc (unsigned int) ; 
 int /*<<< orphan*/  kernel_stack_size ; 
 int /*<<< orphan*/  kfree (void*,unsigned int) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pset0 ; 
 int /*<<< orphan*/  queue_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ queue_first (int /*<<< orphan*/ *) ; 
 scalar_t__ queue_next (int /*<<< orphan*/ *) ; 
 unsigned int round_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasks_threads_lock ; 
 int /*<<< orphan*/  thread_deallocate (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_reference_internal (TYPE_1__*) ; 
 int /*<<< orphan*/  threads ; 
 unsigned int threads_count ; 

kern_return_t
processor_set_stack_usage(
	processor_set_t	pset,
	unsigned int	*totalp,
	vm_size_t	*spacep,
	vm_size_t	*residentp,
	vm_size_t	*maxusagep,
	vm_offset_t	*maxstackp)
{
#if !MACH_DEBUG
        return KERN_NOT_SUPPORTED;
#else
	unsigned int total;
	vm_size_t maxusage;
	vm_offset_t maxstack;

	thread_t *thread_list;
	thread_t thread;

	unsigned int actual;	/* this many things */
	unsigned int i;

	vm_size_t size, size_needed;
	void *addr;

	if (pset == PROCESSOR_SET_NULL || pset != &pset0)
		return KERN_INVALID_ARGUMENT;

	size = 0;
	addr = NULL;

	for (;;) {
		lck_mtx_lock(&tasks_threads_lock);

		actual = threads_count;

		/* do we have the memory we need? */

		size_needed = actual * sizeof(thread_t);
		if (size_needed <= size)
			break;

		lck_mtx_unlock(&tasks_threads_lock);

		if (size != 0)
			kfree(addr, size);

		assert(size_needed > 0);
		size = size_needed;

		addr = kalloc(size);
		if (addr == 0)
			return KERN_RESOURCE_SHORTAGE;
	}

	/* OK, have memory and list is locked */
	thread_list = (thread_t *) addr;
	for (i = 0, thread = (thread_t)(void *) queue_first(&threads);
					!queue_end(&threads, (queue_entry_t) thread);
					thread = (thread_t)(void *) queue_next(&thread->threads)) {
		thread_reference_internal(thread);
		thread_list[i++] = thread;
	}
	assert(i <= actual);

	lck_mtx_unlock(&tasks_threads_lock);

	/* calculate maxusage and free thread references */

	total = 0;
	maxusage = 0;
	maxstack = 0;
	while (i > 0) {
		thread_t threadref = thread_list[--i];

		if (threadref->kernel_stack != 0)
			total++;

		thread_deallocate(threadref);
	}

	if (size != 0)
		kfree(addr, size);

	*totalp = total;
	*residentp = *spacep = total * round_page(kernel_stack_size);
	*maxusagep = maxusage;
	*maxstackp = maxstack;
	return KERN_SUCCESS;

#endif	/* MACH_DEBUG */
}