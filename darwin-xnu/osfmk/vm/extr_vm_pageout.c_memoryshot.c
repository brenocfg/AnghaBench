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
 int /*<<< orphan*/  DBG_MACH_VM_PRESSURE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT1 (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int MACHDBG_CODE (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ vm_debug_events ; 
 int /*<<< orphan*/  vm_page_active_count ; 
 int /*<<< orphan*/  vm_page_free_count ; 
 int /*<<< orphan*/  vm_page_inactive_count ; 
 int /*<<< orphan*/  vm_page_speculative_count ; 
 int /*<<< orphan*/  vm_page_throttled_count ; 

void inline memoryshot(unsigned int event, unsigned int control)
{
	if (vm_debug_events) {
		KERNEL_DEBUG_CONSTANT1((MACHDBG_CODE(DBG_MACH_VM_PRESSURE, event)) | control,
					vm_page_active_count, vm_page_inactive_count,
					vm_page_free_count, vm_page_speculative_count,
					vm_page_throttled_count);
	} else {
		(void) event;
		(void) control;
	}

}