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
typedef  size_t u64 ;
struct power_event {size_t cpu; scalar_t__ state; scalar_t__ start_time; void* next; int /*<<< orphan*/  type; void* end_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSTATE ; 
 int /*<<< orphan*/  PSTATE ; 
 scalar_t__* cpus_cstate_start_times ; 
 scalar_t__* cpus_cstate_state ; 
 scalar_t__* cpus_pstate_start_times ; 
 scalar_t__* cpus_pstate_state ; 
 scalar_t__ first_time ; 
 void* last_time ; 
 scalar_t__ min_freq ; 
 size_t numcpus ; 
 void* power_events ; 
 struct power_event* zalloc (int) ; 

__attribute__((used)) static void end_sample_processing(void)
{
	u64 cpu;
	struct power_event *pwr;

	for (cpu = 0; cpu <= numcpus; cpu++) {
		/* C state */
#if 0
		pwr = zalloc(sizeof(*pwr));
		if (!pwr)
			return;

		pwr->state = cpus_cstate_state[cpu];
		pwr->start_time = cpus_cstate_start_times[cpu];
		pwr->end_time = last_time;
		pwr->cpu = cpu;
		pwr->type = CSTATE;
		pwr->next = power_events;

		power_events = pwr;
#endif
		/* P state */

		pwr = zalloc(sizeof(*pwr));
		if (!pwr)
			return;

		pwr->state = cpus_pstate_state[cpu];
		pwr->start_time = cpus_pstate_start_times[cpu];
		pwr->end_time = last_time;
		pwr->cpu = cpu;
		pwr->type = PSTATE;
		pwr->next = power_events;

		if (!pwr->start_time)
			pwr->start_time = first_time;
		if (!pwr->state)
			pwr->state = min_freq;
		power_events = pwr;
	}
}