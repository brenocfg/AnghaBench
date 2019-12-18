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
 int /*<<< orphan*/  __ftrace_trace_function (unsigned long,unsigned long) ; 
 scalar_t__ function_trace_stop ; 

__attribute__((used)) static void ftrace_test_stop_func(unsigned long ip, unsigned long parent_ip)
{
	if (function_trace_stop)
		return;

	__ftrace_trace_function(ip, parent_ip);
}