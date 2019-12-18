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
struct seq_file {int dummy; } ;
struct TYPE_2__ {int nr_entries; } ;

/* Variables and functions */
 void* SEQ_START_TOKEN ; 
 scalar_t__ ULONG_MAX ; 
 int /*<<< orphan*/  max_stack_size ; 
 TYPE_1__ max_stack_trace ; 
 int /*<<< orphan*/  print_disabled (struct seq_file*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,long,...) ; 
 int* stack_dump_index ; 
 scalar_t__* stack_dump_trace ; 
 int /*<<< orphan*/  stack_tracer_enabled ; 
 int /*<<< orphan*/  trace_lookup_stack (struct seq_file*,long) ; 

__attribute__((used)) static int t_show(struct seq_file *m, void *v)
{
	long i;
	int size;

	if (v == SEQ_START_TOKEN) {
		seq_printf(m, "        Depth    Size   Location"
			   "    (%d entries)\n"
			   "        -----    ----   --------\n",
			   max_stack_trace.nr_entries - 1);

		if (!stack_tracer_enabled && !max_stack_size)
			print_disabled(m);

		return 0;
	}

	i = *(long *)v;

	if (i >= max_stack_trace.nr_entries ||
	    stack_dump_trace[i] == ULONG_MAX)
		return 0;

	if (i+1 == max_stack_trace.nr_entries ||
	    stack_dump_trace[i+1] == ULONG_MAX)
		size = stack_dump_index[i];
	else
		size = stack_dump_index[i] - stack_dump_index[i+1];

	seq_printf(m, "%3ld) %8d   %5d   ", i, stack_dump_index[i], size);

	trace_lookup_stack(m, i);

	return 0;
}