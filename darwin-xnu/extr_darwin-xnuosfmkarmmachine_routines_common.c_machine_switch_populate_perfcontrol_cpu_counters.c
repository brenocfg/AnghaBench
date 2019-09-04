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
struct perfcontrol_cpu_counters {scalar_t__ cycles; scalar_t__ instructions; } ;

/* Variables and functions */

__attribute__((used)) static void
machine_switch_populate_perfcontrol_cpu_counters(struct perfcontrol_cpu_counters *cpu_counters)
{
#if MONOTONIC
	mt_perfcontrol(&cpu_counters->instructions, &cpu_counters->cycles);
#else /* MONOTONIC */
	cpu_counters->instructions = 0;
	cpu_counters->cycles = 0;
#endif /* !MONOTONIC */
}