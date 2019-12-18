#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  TYPE_3__* thread_kernel_state_t ;
typedef  int mach_msg_type_number_t ;
typedef  int mach_exception_data_type_t ;
typedef  int /*<<< orphan*/  instr16 ;
typedef  int /*<<< orphan*/  instr ;
typedef  int /*<<< orphan*/  exception_type_t ;
typedef  scalar_t__ boolean_t ;
typedef  int /*<<< orphan*/  arm_saved_state_t ;
struct TYPE_5__ {scalar_t__ kstackptr; } ;
struct TYPE_8__ {TYPE_1__ machine; } ;
struct TYPE_6__ {int /*<<< orphan*/  ss; } ;
struct TYPE_7__ {TYPE_2__ machine; } ;

/* Variables and functions */
 int /*<<< orphan*/  COPYIN (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  DebuggerCall (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int EXC_ARM_BREAKPOINT ; 
 int EXC_ARM_UNDEFINED ; 
 int /*<<< orphan*/  EXC_BAD_INSTRUCTION ; 
 int /*<<< orphan*/  EXC_BREAKPOINT ; 
 scalar_t__ FALSE ; 
 int FASTTRAP_ARM32_INSTR ; 
 int FASTTRAP_ARM32_RET_INSTR ; 
 int FASTTRAP_ARM64_INSTR ; 
 int FASTTRAP_ARM64_RET_INSTR ; 
 scalar_t__ FASTTRAP_THUMB32_INSTR ; 
 scalar_t__ FASTTRAP_THUMB32_RET_INSTR ; 
 scalar_t__ IS_ARM_GDB_TRAP (int) ; 
 scalar_t__ IS_THUMB_GDB_TRAP (int) ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ PSR64_IS_KERNEL (int) ; 
 scalar_t__ PSR64_IS_USER32 (int) ; 
 scalar_t__ PSR64_IS_USER64 (int) ; 
 int PSR64_MODE_USER32_THUMB ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_4__* current_thread () ; 
 scalar_t__ dtrace_user_probe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exception_triage (int /*<<< orphan*/ ,int*,int) ; 
 int get_saved_state_cpsr (int /*<<< orphan*/ *) ; 
 scalar_t__ get_saved_state_pc (int /*<<< orphan*/ *) ; 
 scalar_t__ ml_set_interrupts_enabled (scalar_t__) ; 
 int /*<<< orphan*/  panic (char*,void*,int) ; 
 scalar_t__ tempDTraceTrapHook (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
handle_uncategorized(arm_saved_state_t *state, boolean_t instrLen2)
{
	exception_type_t           exception = EXC_BAD_INSTRUCTION;
	mach_exception_data_type_t codes[2] = {EXC_ARM_UNDEFINED};
	mach_msg_type_number_t     numcodes = 2;
	uint32_t                   instr = 0;

	if (instrLen2) {
		uint16_t instr16 = 0;
		COPYIN(get_saved_state_pc(state), (char *)&instr16, sizeof(instr16));

		instr = instr16;
	} else {
		COPYIN(get_saved_state_pc(state), (char *)&instr, sizeof(instr));
	}

#if CONFIG_DTRACE
	if (tempDTraceTrapHook && (tempDTraceTrapHook(exception, state, 0, 0) == KERN_SUCCESS)) {
		return;
	}

	if (PSR64_IS_USER64(get_saved_state_cpsr(state))) {
		/*
		 * For a 64bit user process, we care about all 4 bytes of the
		 * instr.
		 */
		if (instr == FASTTRAP_ARM64_INSTR || instr == FASTTRAP_ARM64_RET_INSTR) {
			if (dtrace_user_probe(state) == KERN_SUCCESS)
				return;
		}
	} else if (PSR64_IS_USER32(get_saved_state_cpsr(state))) {
		/*
		 * For a 32bit user process, we check for thumb mode, in
		 * which case we only care about a 2 byte instruction length.
		 * For non-thumb mode, we care about all 4 bytes of the instructin.
		 */
		if (get_saved_state_cpsr(state) & PSR64_MODE_USER32_THUMB) {
			if (((uint16_t)instr == FASTTRAP_THUMB32_INSTR) ||
			    ((uint16_t)instr == FASTTRAP_THUMB32_RET_INSTR)) {
				if (dtrace_user_probe(state) == KERN_SUCCESS) {
					return;
				}
			}
		} else {
			if ((instr == FASTTRAP_ARM32_INSTR) ||
			    (instr == FASTTRAP_ARM32_RET_INSTR)) {
				if (dtrace_user_probe(state) == KERN_SUCCESS) {
					return;
				}
			}
		}
	}

#endif /* CONFIG_DTRACE */

	if (PSR64_IS_KERNEL(get_saved_state_cpsr(state))) {
		if (IS_ARM_GDB_TRAP(instr)) {
			boolean_t interrupt_state;
			vm_offset_t kstackptr;
			exception = EXC_BREAKPOINT;

			interrupt_state = ml_set_interrupts_enabled(FALSE);

			/* Save off the context here (so that the debug logic
			 * can see the original state of this thread).
			 */
			kstackptr = (vm_offset_t) current_thread()->machine.kstackptr;
			if (kstackptr) {
				((thread_kernel_state_t) kstackptr)->machine.ss = *state;
			}

			/* Hop into the debugger (typically either due to a
			 * fatal exception, an explicit panic, or a stackshot
			 * request.
			 */
			DebuggerCall(exception, state);

			(void) ml_set_interrupts_enabled(interrupt_state);
			return;
		} else {
			panic("Undefined kernel instruction: pc=%p instr=%x\n", (void*)get_saved_state_pc(state), instr);
		}
	}

	/*
	 * Check for GDB  breakpoint via illegal opcode.
	 */
	if (instrLen2) {
		if (IS_THUMB_GDB_TRAP(instr)) {
			exception = EXC_BREAKPOINT;
			codes[0] = EXC_ARM_BREAKPOINT;
			codes[1] = instr;
		} else {
			codes[1] = instr;
		}
	} else {
		if (IS_ARM_GDB_TRAP(instr)) {
			exception = EXC_BREAKPOINT;
			codes[0] = EXC_ARM_BREAKPOINT;
			codes[1] = instr;
		} else if (IS_THUMB_GDB_TRAP((instr & 0xFFFF))) {
			exception = EXC_BREAKPOINT;
			codes[0] = EXC_ARM_BREAKPOINT;
			codes[1] = instr & 0xFFFF;
		} else if (IS_THUMB_GDB_TRAP((instr >> 16))) {
			exception = EXC_BREAKPOINT;
			codes[0] = EXC_ARM_BREAKPOINT;
			codes[1] = instr >> 16;
		} else {
			codes[1] = instr;
		}
	}

	exception_triage(exception, codes, numcodes);
	assert(0); /* NOTREACHED */
}