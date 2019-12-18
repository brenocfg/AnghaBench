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
struct vmap_area {int flags; struct vm_struct* private; } ;
struct vm_struct {int dummy; } ;

/* Variables and functions */
 int VM_VM_AREA ; 
 struct vmap_area* find_vmap_area (unsigned long) ; 

__attribute__((used)) static struct vm_struct *find_vm_area(const void *addr)
{
	struct vmap_area *va;

	va = find_vmap_area((unsigned long)addr);
	if (va && va->flags & VM_VM_AREA)
		return va->private;

	return NULL;
}