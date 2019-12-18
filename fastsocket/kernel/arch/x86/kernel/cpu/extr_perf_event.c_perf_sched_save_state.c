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
struct perf_sched {size_t saved_states; int /*<<< orphan*/  state; int /*<<< orphan*/ * saved; } ;

/* Variables and functions */
 size_t SCHED_STATES_MAX ; 
 scalar_t__ WARN_ON_ONCE (int) ; 

__attribute__((used)) static void perf_sched_save_state(struct perf_sched *sched)
{
	if (WARN_ON_ONCE(sched->saved_states >= SCHED_STATES_MAX))
		return;

	sched->saved[sched->saved_states] = sched->state;
	sched->saved_states++;
}