#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* ftrace_func_t ;
struct TYPE_3__ {int flags; void* func; struct TYPE_3__* next; } ;

/* Variables and functions */
 int FTRACE_OPS_FL_DYNAMIC ; 
 void* __ftrace_trace_function ; 
 void* __ftrace_trace_function_delay ; 
 TYPE_1__ ftrace_list_end ; 
 TYPE_1__* ftrace_ops_list ; 
 void* ftrace_ops_list_func ; 
 void* ftrace_test_stop_func ; 
 void* ftrace_trace_function ; 
 int /*<<< orphan*/  update_global_ops () ; 

__attribute__((used)) static void update_ftrace_function(void)
{
	ftrace_func_t func;

	update_global_ops();

	/*
	 * If we are at the end of the list and this ops is
	 * not dynamic, then have the mcount trampoline call
	 * the function directly
	 */
	if (ftrace_ops_list == &ftrace_list_end ||
	    (ftrace_ops_list->next == &ftrace_list_end &&
	     !(ftrace_ops_list->flags & FTRACE_OPS_FL_DYNAMIC)))
		func = ftrace_ops_list->func;
	else
		func = ftrace_ops_list_func;

#ifdef CONFIG_HAVE_FUNCTION_TRACE_MCOUNT_TEST
	ftrace_trace_function = func;
#else
#ifdef CONFIG_DYNAMIC_FTRACE
	/* do not update till all functions have been modified */
	__ftrace_trace_function_delay = func;
#else
	__ftrace_trace_function = func;
#endif
	ftrace_trace_function = ftrace_test_stop_func;
#endif
}