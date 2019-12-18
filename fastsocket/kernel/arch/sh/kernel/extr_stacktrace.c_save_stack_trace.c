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
struct stack_trace {scalar_t__ nr_entries; scalar_t__ max_entries; int /*<<< orphan*/ * entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  ULONG_MAX ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ current_stack_pointer ; 
 int /*<<< orphan*/  save_stack_ops ; 
 int /*<<< orphan*/  unwind_stack (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long*,int /*<<< orphan*/ *,struct stack_trace*) ; 

void save_stack_trace(struct stack_trace *trace)
{
	unsigned long *sp = (unsigned long *)current_stack_pointer;

	unwind_stack(current, NULL, sp,  &save_stack_ops, trace);
	if (trace->nr_entries < trace->max_entries)
		trace->entries[trace->nr_entries++] = ULONG_MAX;
}