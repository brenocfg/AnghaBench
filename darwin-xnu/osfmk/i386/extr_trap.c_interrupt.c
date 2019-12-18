#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  x86_saved_state_t ;
struct TYPE_11__ {scalar_t__ rip; scalar_t__ rsp; int trapno; int cs; } ;
struct TYPE_16__ {TYPE_1__ isf; } ;
typedef  TYPE_6__ x86_saved_state64_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  scalar_t__ uint64_t ;
struct thread_kernel_state {int dummy; } ;
struct i386_exception_link {int dummy; } ;
struct TYPE_14__ {scalar_t__ earliest_soft_deadline; } ;
struct TYPE_15__ {scalar_t__ deadline; TYPE_4__ queue; } ;
struct TYPE_13__ {TYPE_2__* package; } ;
struct TYPE_17__ {int cpu_nested_istack; scalar_t__ cpu_int_event_time; scalar_t__ cpu_max_observed_int_latency; int cpu_max_observed_int_latency_vector; int cpu_kernel_stack; int /*<<< orphan*/  cpu_signals; int /*<<< orphan*/  cpu_prior_signals; TYPE_5__ rtclock_timer; int /*<<< orphan*/  cpu_nested_istack_events; int /*<<< orphan*/ * cpu_hwIntpexits; TYPE_3__ lcpu; } ;
typedef  TYPE_7__ cpu_data_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_18__ {scalar_t__ nLThreadsPerPackage; } ;
struct TYPE_12__ {scalar_t__ num_idle; } ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int DBG_INTR_TYPE_IPI ; 
 int DBG_INTR_TYPE_OTHER ; 
 int DBG_INTR_TYPE_TIMER ; 
 int DBG_INTR_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  DBG_MACH_EXCP_INTR ; 
 int /*<<< orphan*/  DBG_MACH_SCHED ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KDBG_RELEASE (int,int) ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int,long,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,int,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int LAPIC_DEFAULT_INTERRUPT_BASE ; 
 int LAPIC_INTERPROCESSOR_INTERRUPT ; 
 int LAPIC_TIMER_INTERRUPT ; 
 int MACHDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACH_STACK_DEPTH ; 
 int /*<<< orphan*/  PE_incoming_interrupt (int) ; 
 int /*<<< orphan*/  SCHED_STATS_INTERRUPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCOAL_DEBUG (int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ TCOAL_ILAT_THRESHOLD ; 
 scalar_t__ TRUE ; 
 scalar_t__ VM_KERNEL_UNSLIDE (scalar_t__) ; 
 scalar_t__ __improbable (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_7__** cpu_data_ptr ; 
 int cpu_number () ; 
 int /*<<< orphan*/  current_processor () ; 
 int get_preemption_level () ; 
 scalar_t__ ilat_assert ; 
 scalar_t__ interrupt_coalesced_timers ; 
 scalar_t__ interrupt_latency_cap ; 
 scalar_t__ interrupt_timer_coalescing_enabled ; 
 scalar_t__ kernel_stack_depth_max ; 
 int /*<<< orphan*/  kperf_interrupt () ; 
 int /*<<< orphan*/  lapic_interrupt (int,int /*<<< orphan*/ *) ; 
 scalar_t__ mach_absolute_time () ; 
 int /*<<< orphan*/  machine_timeout_suspended () ; 
 int master_cpu ; 
 int /*<<< orphan*/  ml_entropy_collect () ; 
 scalar_t__ ml_get_interrupts_enabled () ; 
 int /*<<< orphan*/  panic (char*,int,scalar_t__,int,...) ; 
 int /*<<< orphan*/  rtclock_intr (int /*<<< orphan*/ *) ; 
 TYPE_6__* saved_state64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  telemetry_mark_curthread (scalar_t__,scalar_t__) ; 
 scalar_t__ telemetry_needs_record ; 
 TYPE_8__ topoParms ; 

void
interrupt(x86_saved_state_t *state)
{
	uint64_t	rip;
	uint64_t	rsp;
	int		interrupt_num;
	boolean_t	user_mode = FALSE;
	int		ipl;
	int		cnum = cpu_number();
	cpu_data_t	*cdp = cpu_data_ptr[cnum];
	int		itype = DBG_INTR_TYPE_UNKNOWN;

        x86_saved_state64_t	*state64 = saved_state64(state);
	rip = state64->isf.rip;
	rsp = state64->isf.rsp;
	interrupt_num = state64->isf.trapno;
	if(state64->isf.cs & 0x03)
		user_mode = TRUE;

	if (cpu_data_ptr[cnum]->lcpu.package->num_idle == topoParms.nLThreadsPerPackage)
		cpu_data_ptr[cnum]->cpu_hwIntpexits[interrupt_num]++;

	if (interrupt_num == (LAPIC_DEFAULT_INTERRUPT_BASE + LAPIC_INTERPROCESSOR_INTERRUPT))
		itype = DBG_INTR_TYPE_IPI;
	else if (interrupt_num == (LAPIC_DEFAULT_INTERRUPT_BASE + LAPIC_TIMER_INTERRUPT))
		itype = DBG_INTR_TYPE_TIMER;
	else
		itype = DBG_INTR_TYPE_OTHER;

	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE, 
		MACHDBG_CODE(DBG_MACH_EXCP_INTR, 0) | DBG_FUNC_START,
		interrupt_num,
		(user_mode ? rip : VM_KERNEL_UNSLIDE(rip)),
		user_mode, itype, 0);

	SCHED_STATS_INTERRUPT(current_processor());

#if CONFIG_TELEMETRY
	if (telemetry_needs_record) {
		telemetry_mark_curthread(user_mode, FALSE);
	}
#endif

	ipl = get_preemption_level();
	
	/*
	 * Handle local APIC interrupts
	 * else call platform expert for devices.
	 */
	if (!lapic_interrupt(interrupt_num, state)) {
		PE_incoming_interrupt(interrupt_num);
	}

	if (__improbable(get_preemption_level() != ipl)) {
		panic("Preemption level altered by interrupt vector 0x%x: initial 0x%x, final: 0x%x\n", interrupt_num, ipl, get_preemption_level());
	}


 	if (__improbable(cdp->cpu_nested_istack)) {
 		cdp->cpu_nested_istack_events++;
 	}
 	else  {
		uint64_t ctime = mach_absolute_time();
		uint64_t int_latency = ctime - cdp->cpu_int_event_time;
		uint64_t esdeadline, ehdeadline;
		/* Attempt to process deferred timers in the context of
		 * this interrupt, unless interrupt time has already exceeded
		 * TCOAL_ILAT_THRESHOLD.
		 */
#define TCOAL_ILAT_THRESHOLD (30000ULL)

		if ((int_latency < TCOAL_ILAT_THRESHOLD) &&
		    interrupt_timer_coalescing_enabled) {
			esdeadline = cdp->rtclock_timer.queue.earliest_soft_deadline;
			ehdeadline = cdp->rtclock_timer.deadline;
			if ((ctime >= esdeadline) && (ctime < ehdeadline)) {
				interrupt_coalesced_timers++;
				TCOAL_DEBUG(0x88880000 | DBG_FUNC_START, ctime, esdeadline, ehdeadline, interrupt_coalesced_timers, 0);
				rtclock_intr(state);
				TCOAL_DEBUG(0x88880000 | DBG_FUNC_END, ctime, esdeadline, interrupt_coalesced_timers, 0, 0);
			} else {
				TCOAL_DEBUG(0x77770000, ctime, cdp->rtclock_timer.queue.earliest_soft_deadline, cdp->rtclock_timer.deadline, interrupt_coalesced_timers, 0);
			}
		}

		if (__improbable(ilat_assert && (int_latency > interrupt_latency_cap) && !machine_timeout_suspended())) {
			panic("Interrupt vector 0x%x exceeded interrupt latency threshold, 0x%llx absolute time delta, prior signals: 0x%x, current signals: 0x%x", interrupt_num, int_latency, cdp->cpu_prior_signals, cdp->cpu_signals);
		}

		if (__improbable(int_latency > cdp->cpu_max_observed_int_latency)) {
			cdp->cpu_max_observed_int_latency = int_latency;
			cdp->cpu_max_observed_int_latency_vector = interrupt_num;
		}
	}

	/*
	 * Having serviced the interrupt first, look at the interrupted stack depth.
	 */
	if (!user_mode) {
		uint64_t depth = cdp->cpu_kernel_stack
				 + sizeof(struct thread_kernel_state)
				 + sizeof(struct i386_exception_link *)
				 - rsp;
		if (__improbable(depth > kernel_stack_depth_max)) {
			kernel_stack_depth_max = (vm_offset_t)depth;
			KERNEL_DEBUG_CONSTANT(
				MACHDBG_CODE(DBG_MACH_SCHED, MACH_STACK_DEPTH),
				(long) depth, (long) VM_KERNEL_UNSLIDE(rip), 0, 0, 0);
		}
	}

	if (cnum == master_cpu)
		ml_entropy_collect();

#if KPERF
	kperf_interrupt();
#endif /* KPERF */

	KDBG_RELEASE(MACHDBG_CODE(DBG_MACH_EXCP_INTR, 0) | DBG_FUNC_END,
			interrupt_num);

	assert(ml_get_interrupts_enabled() == FALSE);
}