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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  boolean_t ;
typedef  int /*<<< orphan*/  arm_saved_state_t ;

/* Variables and functions */
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  DBG_MACH_EXCP_INTR ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KDBG_RELEASE (int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,unsigned int) ; 
 int MACHDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PSR64_IS_USER (int /*<<< orphan*/ ) ; 
 scalar_t__ VM_KERNEL_UNSLIDE (scalar_t__) ; 
 int /*<<< orphan*/  get_saved_state_cpsr (int /*<<< orphan*/ *) ; 
 scalar_t__ get_saved_state_pc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  telemetry_mark_curthread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ telemetry_needs_record ; 

__attribute__((used)) static void
sleh_interrupt_handler_prologue(arm_saved_state_t *state, unsigned int type)
{
	uint64_t     is_user = PSR64_IS_USER(get_saved_state_cpsr(state));

	uint64_t pc = is_user ? get_saved_state_pc(state) :
	              VM_KERNEL_UNSLIDE(get_saved_state_pc(state));

	KDBG_RELEASE(MACHDBG_CODE(DBG_MACH_EXCP_INTR, 0) | DBG_FUNC_START,
	             0, pc, is_user, type);

#if CONFIG_TELEMETRY
	if (telemetry_needs_record) {
		telemetry_mark_curthread((boolean_t)is_user, FALSE);
	}
#endif /* CONFIG_TELEMETRY */
}