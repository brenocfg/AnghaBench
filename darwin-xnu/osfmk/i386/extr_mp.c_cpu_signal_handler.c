#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  x86_saved_state_t ;
struct TYPE_4__ {int cpu_signals; int cpu_prior_signals; } ;
struct TYPE_3__ {int /*<<< orphan*/  lcpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGLOG (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MP_AST ; 
 int /*<<< orphan*/  MP_CALL ; 
 int /*<<< orphan*/  MP_CALL_PM ; 
 int /*<<< orphan*/  MP_KDP ; 
 int /*<<< orphan*/  MP_TLB_FLUSH ; 
 int /*<<< orphan*/  PM_SAFE_FL_NORMAL ; 
 int /*<<< orphan*/  PM_SAFE_FL_SAFE ; 
 int /*<<< orphan*/  SCHED_STATS_IPI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ast_check (int /*<<< orphan*/ ) ; 
 TYPE_2__** cpu_data_ptr ; 
 int /*<<< orphan*/  cpu_handle ; 
 int cpu_number () ; 
 int /*<<< orphan*/  cpu_to_processor (int) ; 
 TYPE_1__* current_cpu_datap () ; 
 int /*<<< orphan*/  current_processor () ; 
 scalar_t__ i_bit (int /*<<< orphan*/ ,int volatile*) ; 
 int /*<<< orphan*/  i_bit_clear (int /*<<< orphan*/ ,int volatile*) ; 
 int /*<<< orphan*/  kdp_snapshot ; 
 int /*<<< orphan*/  mp_call_PM () ; 
 int /*<<< orphan*/  mp_cpus_call_action () ; 
 int /*<<< orphan*/  mp_kdp_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmSafeMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_update_interrupt () ; 
 scalar_t__ pmsafe_debug ; 
 int /*<<< orphan*/  sync_iss_to_iks (int /*<<< orphan*/ *) ; 

int
cpu_signal_handler(x86_saved_state_t *regs)
{
#if	!MACH_KDP
#pragma unused (regs)
#endif /* !MACH_KDP */
	int		my_cpu;
	volatile int	*my_word;

	SCHED_STATS_IPI(current_processor());

	my_cpu = cpu_number();
	my_word = &cpu_data_ptr[my_cpu]->cpu_signals;
	/* Store the initial set of signals for diagnostics. New
	 * signals could arrive while these are being processed
	 * so it's no more than a hint.
	 */

	cpu_data_ptr[my_cpu]->cpu_prior_signals = *my_word;

	do {
#if	MACH_KDP
		if (i_bit(MP_KDP, my_word)) {
			DBGLOG(cpu_handle,my_cpu,MP_KDP);
			i_bit_clear(MP_KDP, my_word);
/* Ensure that the i386_kernel_state at the base of the
 * current thread's stack (if any) is synchronized with the
 * context at the moment of the interrupt, to facilitate
 * access through the debugger.
 */
			sync_iss_to_iks(regs);
			if (pmsafe_debug && !kdp_snapshot)
				pmSafeMode(&current_cpu_datap()->lcpu, PM_SAFE_FL_SAFE);
			mp_kdp_wait(TRUE, FALSE);
			if (pmsafe_debug && !kdp_snapshot)
				pmSafeMode(&current_cpu_datap()->lcpu, PM_SAFE_FL_NORMAL);
		} else
#endif	/* MACH_KDP */
		if (i_bit(MP_TLB_FLUSH, my_word)) {
			DBGLOG(cpu_handle,my_cpu,MP_TLB_FLUSH);
			i_bit_clear(MP_TLB_FLUSH, my_word);
			pmap_update_interrupt();
		} else if (i_bit(MP_CALL, my_word)) {
			DBGLOG(cpu_handle,my_cpu,MP_CALL);
			i_bit_clear(MP_CALL, my_word);
			mp_cpus_call_action();
		} else if (i_bit(MP_CALL_PM, my_word)) {
			DBGLOG(cpu_handle,my_cpu,MP_CALL_PM);
			i_bit_clear(MP_CALL_PM, my_word);
			mp_call_PM();
		}
		if (regs == NULL) {
			/* Called to poll only for cross-calls and TLB flush */
			break;
		} else if (i_bit(MP_AST, my_word)) {
			DBGLOG(cpu_handle,my_cpu,MP_AST);
			i_bit_clear(MP_AST, my_word);
			ast_check(cpu_to_processor(my_cpu));
		}
	} while (*my_word);

	return 0;
}