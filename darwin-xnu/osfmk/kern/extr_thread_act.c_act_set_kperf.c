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
typedef  scalar_t__ thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  AST_KPERF ; 
 int /*<<< orphan*/  act_set_ast (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ current_thread () ; 
 int /*<<< orphan*/  ml_get_interrupts_enabled () ; 
 int /*<<< orphan*/  panic (char*) ; 

void
act_set_kperf(
	thread_t	thread)
{
	/* safety check */
	if (thread != current_thread())
		if( !ml_get_interrupts_enabled() )
			panic("unsafe act_set_kperf operation");

	act_set_ast( thread, AST_KPERF );
}