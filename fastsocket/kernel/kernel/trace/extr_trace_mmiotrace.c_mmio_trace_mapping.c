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
struct trace_array_cpu {int dummy; } ;
struct trace_array {struct trace_array_cpu** data; } ;
struct mmiotrace_map {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __trace_mmiotrace_map (struct trace_array*,struct trace_array_cpu*,struct mmiotrace_map*) ; 
 struct trace_array* mmio_trace_array ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 size_t smp_processor_id () ; 

void mmio_trace_mapping(struct mmiotrace_map *map)
{
	struct trace_array *tr = mmio_trace_array;
	struct trace_array_cpu *data;

	preempt_disable();
	data = tr->data[smp_processor_id()];
	__trace_mmiotrace_map(tr, data, map);
	preempt_enable();
}