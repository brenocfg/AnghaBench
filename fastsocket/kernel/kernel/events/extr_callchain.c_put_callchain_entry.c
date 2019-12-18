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
 int /*<<< orphan*/  __get_cpu_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callchain_recursion ; 
 int /*<<< orphan*/  put_recursion_context (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
put_callchain_entry(int rctx)
{
	put_recursion_context(__get_cpu_var(callchain_recursion), rctx);
}