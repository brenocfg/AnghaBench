#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {scalar_t__ state; int /*<<< orphan*/  stopped; } ;
struct TYPE_5__ {TYPE_1__ lcpu; } ;
typedef  TYPE_2__ cpu_data_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ LCPU_HALT ; 
 scalar_t__ LCPU_OFF ; 
 TYPE_2__* cpu_datap (int) ; 
 int /*<<< orphan*/  cpu_pause () ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_safe_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 scalar_t__ rdtsc64 () ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x86_topo_lock ; 

void
cpu_exit_wait(
	int cpu)
{
    	cpu_data_t	*cdp = cpu_datap(cpu);
	boolean_t	intrs_enabled;
	uint64_t	tsc_timeout;

	/*
	 * Wait until the CPU indicates that it has stopped.
	 * Disable interrupts while the topo lock is held -- arguably
	 * this should always be done but in this instance it can lead to
	 * a timeout if long-running interrupt were to occur here.
	 */
	intrs_enabled = ml_set_interrupts_enabled(FALSE);
	mp_safe_spin_lock(&x86_topo_lock);
	/* Set a generous timeout of several seconds (in TSC ticks) */
	tsc_timeout = rdtsc64() + (10ULL * 1000 * 1000 * 1000);
	while ((cdp->lcpu.state != LCPU_HALT)
	       && (cdp->lcpu.state != LCPU_OFF)
	       && !cdp->lcpu.stopped) {
	    simple_unlock(&x86_topo_lock);
	    ml_set_interrupts_enabled(intrs_enabled);
	    cpu_pause();
	    if (rdtsc64() > tsc_timeout)
		panic("cpu_exit_wait(%d) timeout", cpu);
	    ml_set_interrupts_enabled(FALSE);
	    mp_safe_spin_lock(&x86_topo_lock);
	}
	simple_unlock(&x86_topo_lock);
	ml_set_interrupts_enabled(intrs_enabled);
}