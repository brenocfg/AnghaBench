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
typedef  int u32 ;
struct TYPE_2__ {int val; } ;

/* Variables and functions */
 int EINVAL ; 
 int TRACE_FUNC_OPT_STACK ; 
 TYPE_1__ func_flags ; 
 int /*<<< orphan*/  register_ftrace_function (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_ops ; 
 int /*<<< orphan*/  trace_stack_ops ; 
 int /*<<< orphan*/  unregister_ftrace_function (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int func_set_flag(u32 old_flags, u32 bit, int set)
{
	if (bit == TRACE_FUNC_OPT_STACK) {
		/* do nothing if already set */
		if (!!set == !!(func_flags.val & TRACE_FUNC_OPT_STACK))
			return 0;

		if (set) {
			unregister_ftrace_function(&trace_ops);
			register_ftrace_function(&trace_stack_ops);
		} else {
			unregister_ftrace_function(&trace_stack_ops);
			register_ftrace_function(&trace_ops);
		}

		return 0;
	}

	return -EINVAL;
}