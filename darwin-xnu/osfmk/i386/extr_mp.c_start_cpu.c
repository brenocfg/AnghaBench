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
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {scalar_t__ starter_cpu; int target_cpu; scalar_t__ target_lapic; } ;
typedef  TYPE_1__ processor_start_info_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_4__ {scalar_t__ cpu_running; } ;

/* Variables and functions */
 scalar_t__ ABS (scalar_t__) ; 
 int /*<<< orphan*/  DBG (char*,void*,int,...) ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TRACE_MP_CPU_START ; 
 scalar_t__ TSC_sync_margin ; 
 int /*<<< orphan*/  atomic_decl (scalar_t__*,int) ; 
 TYPE_2__* cpu_datap (int) ; 
 scalar_t__ cpu_number () ; 
 int /*<<< orphan*/  i386_start_cpu (scalar_t__,int) ; 
 int /*<<< orphan*/  kprintf (char*,int,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mp_wait_for_cpu_up (int,int,int) ; 
 int /*<<< orphan*/  panic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,scalar_t__,scalar_t__) ; 
 scalar_t__ rdtsc64 () ; 
 scalar_t__ tsc_entry_barrier ; 
 scalar_t__ tsc_exit_barrier ; 
 scalar_t__ tsc_target ; 

__attribute__((used)) static void
start_cpu(void *arg)
{
	int			i = 1000;
	processor_start_info_t	*psip = (processor_start_info_t *) arg;

	/* Ignore this if the current processor is not the starter */
	if (cpu_number() != psip->starter_cpu)
		return;

	DBG("start_cpu(%p) about to start cpu %d, lapic %d\n",
		arg, psip->target_cpu, psip->target_lapic);

	KERNEL_DEBUG_CONSTANT(
		TRACE_MP_CPU_START | DBG_FUNC_START,
		psip->target_cpu,
		psip->target_lapic, 0, 0, 0);

	i386_start_cpu(psip->target_lapic, psip->target_cpu);

#ifdef	POSTCODE_DELAY
	/* Wait much longer if postcodes are displayed for a delay period. */
	i *= 10000;
#endif
	DBG("start_cpu(%p) about to wait for cpu %d\n",
		arg, psip->target_cpu);

	mp_wait_for_cpu_up(psip->target_cpu, i*100, 100);

	KERNEL_DEBUG_CONSTANT(
		TRACE_MP_CPU_START | DBG_FUNC_END,
		psip->target_cpu,
		cpu_datap(psip->target_cpu)->cpu_running, 0, 0, 0);

	if (TSC_sync_margin &&
	    cpu_datap(psip->target_cpu)->cpu_running) {
		/*
		 * Compare the TSC from the started processor with ours.
		 * Report and log/panic if it diverges by more than
		 * TSC_sync_margin (TSC_SYNC_MARGIN) ticks. This margin
		 * can be overriden by boot-arg (with 0 meaning no checking).
		 */
		uint64_t	tsc_starter;
		int64_t		tsc_delta;
		atomic_decl(&tsc_entry_barrier, 1);
		while (tsc_entry_barrier != 0)
			;	/* spin for both processors at barrier */
		tsc_starter = rdtsc64();
		atomic_decl(&tsc_exit_barrier, 1);
		while (tsc_exit_barrier != 0)
			;	/* spin for target to store its TSC */
		tsc_delta = tsc_target - tsc_starter;
		kprintf("TSC sync for cpu %d: 0x%016llx delta 0x%llx (%lld)\n",
			psip->target_cpu, tsc_target, tsc_delta, tsc_delta);
		if (ABS(tsc_delta) > (int64_t) TSC_sync_margin) { 
#if DEBUG
			panic(
#else
			printf(
#endif
				"Unsynchronized  TSC for cpu %d: "
					"0x%016llx, delta 0x%llx\n",
				psip->target_cpu, tsc_target, tsc_delta);
		}
	}
}