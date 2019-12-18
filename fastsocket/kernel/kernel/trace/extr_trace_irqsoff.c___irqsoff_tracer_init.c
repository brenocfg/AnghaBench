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
 int TRACE_ITER_LATENCY_FMT ; 
 struct trace_array* irqsoff_trace ; 
 int save_lat_flag ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  start_irqsoff_tracer (struct trace_array*) ; 
 int trace_flags ; 
 scalar_t__ tracing_max_latency ; 
 int /*<<< orphan*/  tracing_reset_online_cpus (struct trace_array*) ; 

__attribute__((used)) static void __irqsoff_tracer_init(struct trace_array *tr)
{
	save_lat_flag = trace_flags & TRACE_ITER_LATENCY_FMT;
	trace_flags |= TRACE_ITER_LATENCY_FMT;

	tracing_max_latency = 0;
	irqsoff_trace = tr;
	/* make sure that the tracer is visible */
	smp_wmb();
	tracing_reset_online_cpus(tr);
	start_irqsoff_tracer(tr);
}