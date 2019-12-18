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
struct ftrace_branch_data {int /*<<< orphan*/  incorrect; int /*<<< orphan*/  correct; } ;

/* Variables and functions */
 int /*<<< orphan*/  trace_likely_condition (struct ftrace_branch_data*,int,int) ; 

void ftrace_likely_update(struct ftrace_branch_data *f, int val, int expect)
{
	/*
	 * I would love to have a trace point here instead, but the
	 * trace point code is so inundated with unlikely and likely
	 * conditions that the recursive nightmare that exists is too
	 * much to try to get working. At least for now.
	 */
	trace_likely_condition(f, val, expect);

	/* FIXME: Make this atomic! */
	if (val == expect)
		f->correct++;
	else
		f->incorrect++;
}