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
 scalar_t__ ftrace_stub ; 
 scalar_t__ ftrace_trace_function ; 
 int /*<<< orphan*/  update_ftrace_function () ; 

__attribute__((used)) static void ftrace_update_pid_func(void)
{
	/* Only do something if we are tracing something */
	if (ftrace_trace_function == ftrace_stub)
		return;

	update_ftrace_function();
}