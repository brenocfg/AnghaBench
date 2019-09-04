#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_map_offset_t ;
struct TYPE_3__ {int /*<<< orphan*/  pmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  THREAD_UNINT ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_NONE ; 
 int /*<<< orphan*/  VM_PROT_READ ; 
 TYPE_1__* current_map () ; 
 scalar_t__ pmap_find_phys (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_fault (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
vm_pre_fault(vm_map_offset_t vaddr)
{
	if (pmap_find_phys(current_map()->pmap, vaddr) == 0) {

		vm_fault(current_map(),      /* map */
			vaddr,		     /* vaddr */
			VM_PROT_READ,        /* fault_type */
			FALSE,  	     /* change_wiring */
			VM_KERN_MEMORY_NONE, /* tag - not wiring */
			THREAD_UNINT,        /* interruptible */
			NULL,                /* caller_pmap */
			0                    /* caller_pmap_addr */);
	}
}