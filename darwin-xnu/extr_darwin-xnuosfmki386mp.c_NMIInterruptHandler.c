#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  x86_saved_state_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  pstr ;
struct TYPE_6__ {int /*<<< orphan*/  cpu_tlb_invalid; int /*<<< orphan*/  lcpu; } ;
struct TYPE_4__ {scalar_t__ lock_data; } ;
struct TYPE_5__ {TYPE_1__ interlock; } ;

/* Variables and functions */
 scalar_t__ CROSSCALL_TIMEOUT ; 
 scalar_t__ INTERRUPT_WATCHDOG ; 
 int /*<<< orphan*/  NMIPI_acks ; 
 int /*<<< orphan*/  NMI_count ; 
 scalar_t__ NMI_panic_reason ; 
 int /*<<< orphan*/  PM_SAFE_FL_SAFE ; 
 scalar_t__ SPINLOCK_TIMEOUT ; 
 scalar_t__ TLB_FLUSH_TIMEOUT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  atomic_incl (int /*<<< orphan*/ *,int) ; 
 int cpu_number () ; 
 int /*<<< orphan*/  cpu_pause () ; 
 TYPE_3__* current_cpu_datap () ; 
 int /*<<< orphan*/  current_thread () ; 
 scalar_t__ debugger_cpu ; 
 int /*<<< orphan*/  mach_absolute_time () ; 
 int /*<<< orphan*/  panicDebugging ; 
 scalar_t__ panic_active () ; 
 int /*<<< orphan*/  panic_i386_backtrace (void*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmSafeMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pmsafe_debug ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  spinlock_owner_cpu ; 
 TYPE_2__* spinlock_timed_out ; 
 int /*<<< orphan*/  sync_iss_to_iks_unconditionally (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vector_timed_out ; 

int
NMIInterruptHandler(x86_saved_state_t *regs)
{
	void 		*stackptr;
	char		pstr[192];
	uint64_t	now = mach_absolute_time();

	if (panic_active() && !panicDebugging) {
		if (pmsafe_debug)
			pmSafeMode(&current_cpu_datap()->lcpu, PM_SAFE_FL_SAFE);
		for(;;)
			cpu_pause();
	}

	atomic_incl(&NMIPI_acks, 1);
	atomic_incl(&NMI_count, 1);
	sync_iss_to_iks_unconditionally(regs);
	__asm__ volatile("movq %%rbp, %0" : "=m" (stackptr));

	if (cpu_number() == debugger_cpu)
		goto NMExit;

	if (NMI_panic_reason == SPINLOCK_TIMEOUT) {
		snprintf(&pstr[0], sizeof(pstr),
			"Panic(CPU %d, time %llu): NMIPI for spinlock acquisition timeout, spinlock: %p, spinlock owner: %p, current_thread: %p, spinlock_owner_cpu: 0x%x\n",
			cpu_number(), now, spinlock_timed_out, (void *) spinlock_timed_out->interlock.lock_data, current_thread(), spinlock_owner_cpu);
		panic_i386_backtrace(stackptr, 64, &pstr[0], TRUE, regs);
	} else if (NMI_panic_reason == TLB_FLUSH_TIMEOUT) {
		snprintf(&pstr[0], sizeof(pstr),
			"Panic(CPU %d, time %llu): NMIPI for unresponsive processor: TLB flush timeout, TLB state:0x%x\n",
			cpu_number(), now, current_cpu_datap()->cpu_tlb_invalid);
		panic_i386_backtrace(stackptr, 48, &pstr[0], TRUE, regs);
	} else if (NMI_panic_reason == CROSSCALL_TIMEOUT) {
		snprintf(&pstr[0], sizeof(pstr),
			"Panic(CPU %d, time %llu): NMIPI for unresponsive processor: cross-call timeout\n",
			cpu_number(), now);
		panic_i386_backtrace(stackptr, 64, &pstr[0], TRUE, regs);
	} else if (NMI_panic_reason == INTERRUPT_WATCHDOG) {
		snprintf(&pstr[0], sizeof(pstr),
			"Panic(CPU %d, time %llu): NMIPI for unresponsive processor: interrupt watchdog for vector 0x%x\n",
			cpu_number(), now, vector_timed_out);
		panic_i386_backtrace(stackptr, 64, &pstr[0], TRUE, regs);
	}
	
#if MACH_KDP
	if (pmsafe_debug && !kdp_snapshot)
		pmSafeMode(&current_cpu_datap()->lcpu, PM_SAFE_FL_SAFE);
	current_cpu_datap()->cpu_NMI_acknowledged = TRUE;
	i_bit_clear(MP_KDP, &current_cpu_datap()->cpu_signals);
	if (panic_active() || NMI_panic_reason != NONE) {
		mp_kdp_wait(FALSE, TRUE);
	} else if (!mp_kdp_trap &&
		   !mp_kdp_is_NMI &&
		   virtualized && (debug_boot_arg & DB_NMI)) {
		/*
		 * Under a VMM with the debug boot-arg set, drop into kdp.
		 * Since an NMI is involved, there's a risk of contending with
		 * a panic. And side-effects of NMIs may result in entry into, 
		 * and continuing from, the debugger being unreliable.
		 */
		if (__sync_bool_compare_and_swap(&mp_kdp_is_NMI, FALSE, TRUE)) {
			kprintf_break_lock();
			kprintf("Debugger entry requested by NMI\n");
			kdp_i386_trap(T_DEBUG, saved_state64(regs), 0, 0);
			printf("Debugger entry requested by NMI\n");
			mp_kdp_is_NMI = FALSE;
		} else {
			mp_kdp_wait(FALSE, FALSE);
		}
	} else {
		mp_kdp_wait(FALSE, FALSE);
	}
	if (pmsafe_debug && !kdp_snapshot)
		pmSafeMode(&current_cpu_datap()->lcpu, PM_SAFE_FL_NORMAL);
#endif
NMExit:	
	return 1;
}