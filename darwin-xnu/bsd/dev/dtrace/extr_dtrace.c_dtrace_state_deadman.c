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
typedef  scalar_t__ hrtime_t ;
struct TYPE_4__ {scalar_t__ dts_laststatus; scalar_t__ dts_alive; } ;
typedef  TYPE_1__ dtrace_state_t ;
struct TYPE_5__ {TYPE_1__* dta_state; } ;

/* Variables and functions */
 scalar_t__ INT64_MAX ; 
 TYPE_3__ dtrace_anon ; 
 scalar_t__ dtrace_deadman_user ; 
 scalar_t__ dtrace_gethrtime () ; 
 int /*<<< orphan*/  dtrace_membar_producer () ; 
 int /*<<< orphan*/  dtrace_sync () ; 

__attribute__((used)) static void
dtrace_state_deadman(dtrace_state_t *state)
{
	hrtime_t now;

	dtrace_sync();

	now = dtrace_gethrtime();

	if (state != dtrace_anon.dta_state &&
	    now - state->dts_laststatus >= dtrace_deadman_user)
		return;

	/*
	 * We must be sure that dts_alive never appears to be less than the
	 * value upon entry to dtrace_state_deadman(), and because we lack a
	 * dtrace_cas64(), we cannot store to it atomically.  We thus instead
	 * store INT64_MAX to it, followed by a memory barrier, followed by
	 * the new value.  This assures that dts_alive never appears to be
	 * less than its true value, regardless of the order in which the
	 * stores to the underlying storage are issued.
	 */
	state->dts_alive = INT64_MAX;
	dtrace_membar_producer();
	state->dts_alive = now;
}