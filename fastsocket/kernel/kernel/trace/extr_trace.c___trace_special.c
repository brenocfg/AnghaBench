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
 int /*<<< orphan*/  ftrace_trace_special (void*,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preempt_count () ; 

void
__trace_special(void *__tr, void *__data,
		unsigned long arg1, unsigned long arg2, unsigned long arg3)
{
	ftrace_trace_special(__tr, arg1, arg2, arg3, preempt_count());
}