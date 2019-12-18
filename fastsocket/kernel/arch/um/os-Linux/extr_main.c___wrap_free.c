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

/* Variables and functions */
 int /*<<< orphan*/  __real_free (void*) ; 
 unsigned long end_vm ; 
 unsigned long high_physmem ; 
 int /*<<< orphan*/  kfree (void*) ; 
 scalar_t__ kmalloc_ok ; 
 unsigned long start_vm ; 
 unsigned long uml_physmem ; 
 int /*<<< orphan*/  vfree (void*) ; 

void __wrap_free(void *ptr)
{
	unsigned long addr = (unsigned long) ptr;

	/*
	 * We need to know how the allocation happened, so it can be correctly
	 * freed.  This is done by seeing what region of memory the pointer is
	 * in -
	 * 	physical memory - kmalloc/kfree
	 *	kernel virtual memory - vmalloc/vfree
	 * 	anywhere else - malloc/free
	 * If kmalloc is not yet possible, then either high_physmem and/or
	 * end_vm are still 0 (as at startup), in which case we call free, or
	 * we have set them, but anyway addr has not been allocated from those
	 * areas. So, in both cases __real_free is called.
	 *
	 * CAN_KMALLOC is checked because it would be bad to free a buffer
	 * with kmalloc/vmalloc after they have been turned off during
	 * shutdown.
	 * XXX: However, we sometimes shutdown CAN_KMALLOC temporarily, so
	 * there is a possibility for memory leaks.
	 */

	if ((addr >= uml_physmem) && (addr < high_physmem)) {
		if (kmalloc_ok)
			kfree(ptr);
	}
	else if ((addr >= start_vm) && (addr < end_vm)) {
		if (kmalloc_ok)
			vfree(ptr);
	}
	else __real_free(ptr);
}