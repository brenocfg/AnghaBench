#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct cpu_data {uintptr_t cpu_debug_interface_map; TYPE_1__* cpu_user_debug; } ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_6__ {scalar_t__* wcr; scalar_t__* wvr; scalar_t__* bcr; scalar_t__* bvr; } ;
typedef  TYPE_1__ arm_debug_state_t ;
struct TYPE_7__ {scalar_t__ coprocessor_core_debug; scalar_t__ memory_mapped_core_debug; } ;
typedef  TYPE_2__ arm_debug_info_t ;

/* Variables and functions */
 scalar_t__ volatile ARM_DBGDSCR_MDBGEN ; 
 scalar_t__ ARM_DBG_LOCK_ACCESS_KEY ; 
 scalar_t__ ARM_DEBUG_OFFSET_DBGBCR ; 
 scalar_t__ ARM_DEBUG_OFFSET_DBGBVR ; 
 scalar_t__ ARM_DEBUG_OFFSET_DBGDSCR ; 
 scalar_t__ ARM_DEBUG_OFFSET_DBGLAR ; 
 scalar_t__ ARM_DEBUG_OFFSET_DBGPRSR ; 
 scalar_t__ ARM_DEBUG_OFFSET_DBGWCR ; 
 scalar_t__ ARM_DEBUG_OFFSET_DBGWVR ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_2__* arm_debug_info () ; 
 int /*<<< orphan*/  arm_debug_set_cp14 (TYPE_1__*) ; 
 struct cpu_data* getCpuDatap () ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 

void arm_debug_set(arm_debug_state_t *debug_state)
{
	/* If this CPU supports the memory-mapped debug interface, use it, otherwise
	 * attempt the Extended CP14 interface.  The two routines need to be kept in sync,
	 * functionality-wise.
	 */
	struct cpu_data *cpu_data_ptr;
	arm_debug_info_t *debug_info = arm_debug_info();
	boolean_t       intr;

	intr = ml_set_interrupts_enabled(FALSE);
	cpu_data_ptr = getCpuDatap();

	// Set current user debug
	cpu_data_ptr->cpu_user_debug = debug_state;

	if (debug_info->memory_mapped_core_debug) {
		int i;
		uintptr_t debug_map = cpu_data_ptr->cpu_debug_interface_map;

		// unlock debug registers
		*(volatile uint32_t *)(debug_map + ARM_DEBUG_OFFSET_DBGLAR) = ARM_DBG_LOCK_ACCESS_KEY;

		// read DBGPRSR to clear the sticky power-down bit (necessary to access debug registers)
		*(volatile uint32_t *)(debug_map + ARM_DEBUG_OFFSET_DBGPRSR);

		// enable monitor mode (needed to set and use debug registers)
		*(volatile uint32_t *)(debug_map + ARM_DEBUG_OFFSET_DBGDSCR) |= ARM_DBGDSCR_MDBGEN;

		// first turn off all breakpoints/watchpoints
		for (i = 0; i < 16; i++) {
			((volatile uint32_t *)(debug_map + ARM_DEBUG_OFFSET_DBGBCR))[i] = 0;
			((volatile uint32_t *)(debug_map + ARM_DEBUG_OFFSET_DBGWCR))[i] = 0;
		}

		// if (debug_state == NULL) disable monitor mode
		if (debug_state == NULL) {
			*(volatile uint32_t *)(debug_map + ARM_DEBUG_OFFSET_DBGDSCR) &= ~ARM_DBGDSCR_MDBGEN;
		} else {
			for (i = 0; i < 16; i++) {
				((volatile uint32_t *)(debug_map + ARM_DEBUG_OFFSET_DBGBVR))[i] = debug_state->bvr[i];
				((volatile uint32_t *)(debug_map + ARM_DEBUG_OFFSET_DBGBCR))[i] = debug_state->bcr[i];
				((volatile uint32_t *)(debug_map + ARM_DEBUG_OFFSET_DBGWVR))[i] = debug_state->wvr[i];
				((volatile uint32_t *)(debug_map + ARM_DEBUG_OFFSET_DBGWCR))[i] = debug_state->wcr[i];
			}
		}	    

		// lock debug registers
		*(volatile uint32_t *)(debug_map + ARM_DEBUG_OFFSET_DBGLAR) = 0;

    } else if (debug_info->coprocessor_core_debug) {
		arm_debug_set_cp14(debug_state);
	}

	(void) ml_set_interrupts_enabled(intr);

	return;
}