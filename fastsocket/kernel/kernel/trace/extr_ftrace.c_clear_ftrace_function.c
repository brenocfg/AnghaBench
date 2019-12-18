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
 void* __ftrace_trace_function ; 
 void* __ftrace_trace_function_delay ; 
 void* ftrace_pid_function ; 
 void* ftrace_stub ; 
 void* ftrace_trace_function ; 

void clear_ftrace_function(void)
{
	ftrace_trace_function = ftrace_stub;
	__ftrace_trace_function = ftrace_stub;
	__ftrace_trace_function_delay = ftrace_stub;
	ftrace_pid_function = ftrace_stub;
}