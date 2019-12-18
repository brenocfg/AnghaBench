#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cpudata {int /*<<< orphan*/  timer; TYPE_1__* pstate_policy; } ;
struct TYPE_2__ {int sample_rate_ms; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer_pinned (int /*<<< orphan*/ *,scalar_t__) ; 
 int msecs_to_jiffies (int) ; 

__attribute__((used)) static inline void intel_pstate_set_sample_time(struct cpudata *cpu)
{
	int sample_time, delay;

	sample_time = cpu->pstate_policy->sample_rate_ms;
	delay = msecs_to_jiffies(sample_time);
	mod_timer_pinned(&cpu->timer, jiffies + delay);
}