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

/* Variables and functions */
 int /*<<< orphan*/  CALLER_ADDR0 ; 
 int /*<<< orphan*/  CALLER_ADDR1 ; 
 scalar_t__ irq_trace () ; 
 scalar_t__ preempt_trace () ; 
 int /*<<< orphan*/  stop_critical_timing (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void stop_critical_timings(void)
{
	if (preempt_trace() || irq_trace())
		stop_critical_timing(CALLER_ADDR0, CALLER_ADDR1);
}