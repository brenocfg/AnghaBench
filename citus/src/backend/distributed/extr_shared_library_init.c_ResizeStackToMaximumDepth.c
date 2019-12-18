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
 int /*<<< orphan*/  DEBUG5 ; 
 char* alloca (long) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char volatile*,char volatile*,char volatile,char volatile) ; 
 long max_stack_depth ; 

__attribute__((used)) static void
ResizeStackToMaximumDepth(void)
{
#ifndef WIN32
	volatile char *stack_resizer = NULL;
	long max_stack_depth_bytes = max_stack_depth * 1024L;

	stack_resizer = alloca(max_stack_depth_bytes);

	/*
	 * Different architectures might have different directions while
	 * growing the stack. So, touch both ends.
	 */
	stack_resizer[0] = 0;
	stack_resizer[max_stack_depth_bytes - 1] = 0;

	/*
	 * Passing the address to external function also prevents the function
	 * from being optimized away, and the debug elog can also help with
	 * diagnosis if needed.
	 */
	elog(DEBUG5, "entry stack is at %p, increased to %p, the top and bottom values of "
				 "the stack is %d and %d", &stack_resizer[0],
		 &stack_resizer[max_stack_depth_bytes - 1],
		 stack_resizer[max_stack_depth_bytes - 1], stack_resizer[0]);

#endif
}