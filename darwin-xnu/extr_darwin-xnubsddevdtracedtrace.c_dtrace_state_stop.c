#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  processorid_t ;
struct TYPE_4__ {scalar_t__ dts_activity; scalar_t__ dts_reserve; } ;
typedef  TYPE_1__ dtrace_state_t ;
typedef  int /*<<< orphan*/  dtrace_icookie_t ;
struct TYPE_5__ {int /*<<< orphan*/  cpu_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 TYPE_3__* CPU ; 
 scalar_t__ DTRACE_ACTIVITY_ACTIVE ; 
 scalar_t__ DTRACE_ACTIVITY_COOLDOWN ; 
 scalar_t__ DTRACE_ACTIVITY_DRAINING ; 
 scalar_t__ DTRACE_ACTIVITY_STOPPED ; 
 int EINVAL ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  dtrace_interrupt_disable () ; 
 int /*<<< orphan*/  dtrace_interrupt_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int /*<<< orphan*/  dtrace_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_probeid_end ; 
 int /*<<< orphan*/  dtrace_sync () ; 

__attribute__((used)) static int
dtrace_state_stop(dtrace_state_t *state, processorid_t *cpu)
{
	dtrace_icookie_t cookie;

	LCK_MTX_ASSERT(&dtrace_lock, LCK_MTX_ASSERT_OWNED);

	if (state->dts_activity != DTRACE_ACTIVITY_ACTIVE &&
	    state->dts_activity != DTRACE_ACTIVITY_DRAINING)
		return (EINVAL);

	/*
	 * We'll set the activity to DTRACE_ACTIVITY_DRAINING, and issue a sync
	 * to be sure that every CPU has seen it.  See below for the details
	 * on why this is done.
	 */
	state->dts_activity = DTRACE_ACTIVITY_DRAINING;
	dtrace_sync();

	/*
	 * By this point, it is impossible for any CPU to be still processing
	 * with DTRACE_ACTIVITY_ACTIVE.  We can thus set our activity to
	 * DTRACE_ACTIVITY_COOLDOWN and know that we're not racing with any
	 * other CPU in dtrace_buffer_reserve().  This allows dtrace_probe()
	 * and callees to know that the activity is DTRACE_ACTIVITY_COOLDOWN
	 * iff we're in the END probe.
	 */
	state->dts_activity = DTRACE_ACTIVITY_COOLDOWN;
	dtrace_sync();
	ASSERT(state->dts_activity == DTRACE_ACTIVITY_COOLDOWN);

	/*
	 * Finally, we can release the reserve and call the END probe.  We
	 * disable interrupts across calling the END probe to allow us to
	 * return the CPU on which we actually called the END probe.  This
	 * allows user-land to be sure that this CPU's principal buffer is
	 * processed last.
	 */
	state->dts_reserve = 0;

	cookie = dtrace_interrupt_disable();
	*cpu = CPU->cpu_id;
	dtrace_probe(dtrace_probeid_end,
	    (uint64_t)(uintptr_t)state, 0, 0, 0, 0);
	dtrace_interrupt_enable(cookie);

	state->dts_activity = DTRACE_ACTIVITY_STOPPED;
	dtrace_sync();

	return (0);
}