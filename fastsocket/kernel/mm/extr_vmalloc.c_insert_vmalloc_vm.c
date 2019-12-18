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
struct vmap_area {int dummy; } ;
struct vm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  insert_vmalloc_vmlist (struct vm_struct*) ; 
 int /*<<< orphan*/  setup_vmalloc_vm (struct vm_struct*,struct vmap_area*,unsigned long,void*) ; 

__attribute__((used)) static void insert_vmalloc_vm(struct vm_struct *vm, struct vmap_area *va,
			      unsigned long flags, void *caller)
{
	setup_vmalloc_vm(vm, va, flags, caller);
	insert_vmalloc_vmlist(vm);
}