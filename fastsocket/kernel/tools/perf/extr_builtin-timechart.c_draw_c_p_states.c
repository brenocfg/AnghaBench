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
struct power_event {scalar_t__ type; struct power_event* next; scalar_t__ state; int /*<<< orphan*/  end_time; int /*<<< orphan*/  start_time; int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 scalar_t__ CSTATE ; 
 scalar_t__ PSTATE ; 
 scalar_t__ min_freq ; 
 struct power_event* power_events ; 
 int /*<<< orphan*/  svg_cstate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  svg_pstate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void draw_c_p_states(void)
{
	struct power_event *pwr;
	pwr = power_events;

	/*
	 * two pass drawing so that the P state bars are on top of the C state blocks
	 */
	while (pwr) {
		if (pwr->type == CSTATE)
			svg_cstate(pwr->cpu, pwr->start_time, pwr->end_time, pwr->state);
		pwr = pwr->next;
	}

	pwr = power_events;
	while (pwr) {
		if (pwr->type == PSTATE) {
			if (!pwr->state)
				pwr->state = min_freq;
			svg_pstate(pwr->cpu, pwr->start_time, pwr->end_time, pwr->state);
		}
		pwr = pwr->next;
	}
}