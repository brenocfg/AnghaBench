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
typedef  int /*<<< orphan*/  u64 ;
struct power_event {int cpu; struct power_event* next; int /*<<< orphan*/  type; int /*<<< orphan*/  end_time; int /*<<< orphan*/  start_time; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSTATE ; 
 int /*<<< orphan*/ * cpus_cstate_start_times ; 
 int /*<<< orphan*/ * cpus_cstate_state ; 
 struct power_event* power_events ; 
 struct power_event* zalloc (int) ; 

__attribute__((used)) static void c_state_end(int cpu, u64 timestamp)
{
	struct power_event *pwr = zalloc(sizeof(*pwr));

	if (!pwr)
		return;

	pwr->state = cpus_cstate_state[cpu];
	pwr->start_time = cpus_cstate_start_times[cpu];
	pwr->end_time = timestamp;
	pwr->cpu = cpu;
	pwr->type = CSTATE;
	pwr->next = power_events;

	power_events = pwr;
}