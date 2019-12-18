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
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  ftrace_pid_function (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  test_tsk_trace_trace (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ftrace_pid_func(unsigned long ip, unsigned long parent_ip)
{
	if (!test_tsk_trace_trace(current))
		return;

	ftrace_pid_function(ip, parent_ip);
}