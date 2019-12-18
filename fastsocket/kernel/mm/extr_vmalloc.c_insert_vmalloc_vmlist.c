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
struct vm_struct {scalar_t__ addr; struct vm_struct* next; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_UNLIST ; 
 struct vm_struct* vmlist ; 
 int /*<<< orphan*/  vmlist_lock ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void insert_vmalloc_vmlist(struct vm_struct *vm)
{
	struct vm_struct *tmp, **p;

	vm->flags &= ~VM_UNLIST;
	write_lock(&vmlist_lock);
	for (p = &vmlist; (tmp = *p) != NULL; p = &tmp->next) {
		if (tmp->addr >= vm->addr)
			break;
	}
	vm->next = *p;
	*p = vm;
	write_unlock(&vmlist_lock);
}