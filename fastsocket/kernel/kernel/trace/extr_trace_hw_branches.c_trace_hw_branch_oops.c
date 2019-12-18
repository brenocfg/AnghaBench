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
 int /*<<< orphan*/  ds_resume_bts_noirq (scalar_t__) ; 
 int /*<<< orphan*/  ds_suspend_bts_noirq (scalar_t__) ; 
 int /*<<< orphan*/  hw_branch_trace ; 
 scalar_t__ this_tracer ; 
 int /*<<< orphan*/  trace_bts_cpu (int /*<<< orphan*/ ) ; 

void trace_hw_branch_oops(void)
{
	if (this_tracer) {
		ds_suspend_bts_noirq(this_tracer);
		trace_bts_cpu(hw_branch_trace);
		ds_resume_bts_noirq(this_tracer);
	}
}