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
typedef  int vm_prot_t ;
typedef  void* vm_offset_t ;
typedef  TYPE_1__* vm_map_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  TYPE_2__* thread_t ;
typedef  int mach_msg_type_number_t ;
typedef  void* mach_exception_data_type_t ;
typedef  scalar_t__ kern_return_t ;
typedef  scalar_t__ fault_status_t ;
typedef  int /*<<< orphan*/  exception_type_t ;
typedef  int /*<<< orphan*/  boolean_t ;
typedef  int /*<<< orphan*/  arm_saved_state_t ;
struct TYPE_7__ {int options; TYPE_1__* map; int /*<<< orphan*/  iotier_override; } ;
struct TYPE_6__ {int /*<<< orphan*/  pmap; } ;

/* Variables and functions */
 void* EXC_ARM_DA_ALIGN ; 
 int /*<<< orphan*/  EXC_BAD_ACCESS ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FSC_SYNC_PARITY ; 
 scalar_t__ KERN_ABORTED ; 
 void* KERN_FAILURE ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  THREAD_ABORTSAFE ; 
 int /*<<< orphan*/  THROTTLE_LEVEL_NONE ; 
 int TH_OPT_DTRACE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_NONE ; 
 int VM_PROT_EXECUTE ; 
 int /*<<< orphan*/  arm64_platform_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ arm_fast_fault (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* current_thread () ; 
 scalar_t__ dtrace_tally_fault (void*) ; 
 int /*<<< orphan*/  exception_triage (int /*<<< orphan*/ ,void**,int) ; 
 scalar_t__ is_alignment_fault (scalar_t__) ; 
 scalar_t__ is_parity_error (scalar_t__) ; 
 int /*<<< orphan*/  is_translation_fault (scalar_t__) ; 
 scalar_t__ is_vm_fault (scalar_t__) ; 
 TYPE_1__* kernel_map ; 
 scalar_t__ ml_at_interrupt_context () ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  panic_with_thread_kernel_state (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ pgtrace_enabled ; 
 scalar_t__ pmap_pgtrace_fault (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_saved_state_pc (int /*<<< orphan*/ *,void*) ; 
 void* tbi_clear (void*) ; 
 int /*<<< orphan*/  thread_exception_return () ; 
 int /*<<< orphan*/  trunc_page (void*) ; 
 scalar_t__ user_tbi_enabled () ; 
 scalar_t__ vm_fault (TYPE_1__*,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
handle_user_abort(arm_saved_state_t *state, uint32_t esr, vm_offset_t fault_addr,
				  fault_status_t fault_code, vm_prot_t fault_type, vm_offset_t recover)
{
	exception_type_t		exc = EXC_BAD_ACCESS;
	mach_exception_data_type_t	codes[2];
	mach_msg_type_number_t 		numcodes = 2;
	thread_t			thread = current_thread();

	(void)esr;
	(void)state;

	if (ml_at_interrupt_context())
		panic_with_thread_kernel_state("Apparently on interrupt stack when taking user abort!\n", state);

	thread->iotier_override = THROTTLE_LEVEL_NONE; /* Reset IO tier override before handling abort from userspace */

	if (is_vm_fault(fault_code)) {
		kern_return_t   result = KERN_FAILURE;
		vm_map_t        map = thread->map;
		vm_offset_t     vm_fault_addr = fault_addr;

		assert(map != kernel_map);

		if (!(fault_type & VM_PROT_EXECUTE) && user_tbi_enabled())
				vm_fault_addr = tbi_clear(fault_addr);

#if CONFIG_DTRACE
		if (thread->options & TH_OPT_DTRACE) {	/* Executing under dtrace_probe? */
			if (dtrace_tally_fault(vm_fault_addr)) { /* Should a user mode fault under dtrace be ignored? */
				if (recover) {
					set_saved_state_pc(state, recover);
				} else {
					boolean_t intr = ml_set_interrupts_enabled(FALSE);
					panic_with_thread_kernel_state("copyin/out has no recovery point", state);
					(void) ml_set_interrupts_enabled(intr);
				}
				return;
			} else {
				boolean_t intr = ml_set_interrupts_enabled(FALSE);
				panic_with_thread_kernel_state("Unexpected UMW page fault under dtrace_probe", state);
				(void) ml_set_interrupts_enabled(intr);
				return;
			}
		}
#else
		(void)recover;
#endif

#if CONFIG_PGTRACE
		if (pgtrace_enabled) {
			/* Check to see if trace bit is set */
			result = pmap_pgtrace_fault(map->pmap, fault_addr, state);
			if (result == KERN_SUCCESS) return;
		}
#endif

		/* check to see if it is just a pmap ref/modify fault */

		if ((result != KERN_SUCCESS) && !is_translation_fault(fault_code)) {
			result = arm_fast_fault(map->pmap, trunc_page(vm_fault_addr), fault_type, TRUE);
		}
		if (result != KERN_SUCCESS) {

			{
				/* We have to fault the page in */
				result = vm_fault(map, vm_fault_addr, fault_type,
				                  /* change_wiring */ FALSE, VM_KERN_MEMORY_NONE, THREAD_ABORTSAFE,
				                  /* caller_pmap */ NULL, /* caller_pmap_addr */ 0);
			}
		}
		if (result == KERN_SUCCESS || result == KERN_ABORTED) {
			thread_exception_return();
			/* NOTREACHED */
		}

		codes[0] = result;
	} else if (is_alignment_fault(fault_code)) {
		codes[0] = EXC_ARM_DA_ALIGN;
	} else if (is_parity_error(fault_code)) {
#if defined(APPLE_ARM64_ARCH_FAMILY)
		if (fault_code == FSC_SYNC_PARITY) {
			arm64_platform_error(state, esr, fault_addr);
			thread_exception_return();
			/* NOTREACHED */
		}
#else
		panic("User parity error.");
#endif
	} else {
		codes[0] = KERN_FAILURE;
	}

	codes[1] = fault_addr;
	exception_triage(exc, codes, numcodes);
	assert(0); /* NOTREACHED */
}