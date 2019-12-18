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
struct TYPE_2__ {int val; } ;

/* Variables and functions */
 int TRACE_FUNC_OPT_STACK ; 
 scalar_t__ ftrace_function_enabled ; 
 TYPE_1__ func_flags ; 
 int /*<<< orphan*/  trace_ops ; 
 int /*<<< orphan*/  trace_stack_ops ; 
 int /*<<< orphan*/  unregister_ftrace_function (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tracing_stop_function_trace(void)
{
	ftrace_function_enabled = 0;

	if (func_flags.val & TRACE_FUNC_OPT_STACK)
		unregister_ftrace_function(&trace_stack_ops);
	else
		unregister_ftrace_function(&trace_ops);
}