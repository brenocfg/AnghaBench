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
struct vmap_area {int flags; int /*<<< orphan*/  va_end; int /*<<< orphan*/  va_start; struct vm_struct* private; } ;
struct vm_struct {int flags; int /*<<< orphan*/  size; struct vm_struct* next; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int VM_UNLIST ; 
 int VM_VM_AREA ; 
 struct vmap_area* find_vmap_area (unsigned long) ; 
 int /*<<< orphan*/  free_unmap_vmap_area (struct vmap_area*) ; 
 int /*<<< orphan*/  vmap_debug_free_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vm_struct* vmlist ; 
 int /*<<< orphan*/  vmlist_lock ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

struct vm_struct *remove_vm_area(const void *addr)
{
	struct vmap_area *va;

	va = find_vmap_area((unsigned long)addr);
	if (va && va->flags & VM_VM_AREA) {
		struct vm_struct *vm = va->private;

		if (!(vm->flags & VM_UNLIST)) {
			struct vm_struct *tmp, **p;
			/*
			 * remove from list and disallow access to
			 * this vm_struct before unmap. (address range
			 * confliction is maintained by vmap.)
			 */
			write_lock(&vmlist_lock);
			for (p = &vmlist; (tmp = *p) != vm; p = &tmp->next)
				;
			*p = tmp->next;
			write_unlock(&vmlist_lock);
		}

		vmap_debug_free_range(va->va_start, va->va_end);
		free_unmap_vmap_area(va);
		vm->size -= PAGE_SIZE;

		return vm;
	}
	return NULL;
}