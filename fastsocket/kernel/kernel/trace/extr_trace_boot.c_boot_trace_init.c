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
struct trace_array {int dummy; } ;

/* Variables and functions */
 struct trace_array* boot_trace ; 
 int /*<<< orphan*/  tracing_reset_online_cpus (struct trace_array*) ; 
 int /*<<< orphan*/  tracing_sched_switch_assign_trace (struct trace_array*) ; 

__attribute__((used)) static int boot_trace_init(struct trace_array *tr)
{
	boot_trace = tr;

	if (!tr)
		return 0;

	tracing_reset_online_cpus(tr);

	tracing_sched_switch_assign_trace(tr);
	return 0;
}