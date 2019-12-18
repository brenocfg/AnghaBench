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
struct vmap_area {int /*<<< orphan*/  flags; struct vm_struct* private; scalar_t__ va_start; scalar_t__ va_end; } ;
struct vm_struct {unsigned long flags; void* caller; scalar_t__ size; void* addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_VM_AREA ; 

__attribute__((used)) static void setup_vmalloc_vm(struct vm_struct *vm, struct vmap_area *va,
			      unsigned long flags, void *caller)
{
	vm->flags = flags;
	vm->addr = (void *)va->va_start;
	vm->size = va->va_end - va->va_start;
	vm->caller = caller;
	va->private = vm;
	va->flags |= VM_VM_AREA;
}