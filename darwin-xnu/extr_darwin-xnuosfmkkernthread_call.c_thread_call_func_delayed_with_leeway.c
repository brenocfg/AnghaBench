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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  thread_call_param_t ;
typedef  int /*<<< orphan*/  thread_call_func_t ;

/* Variables and functions */
 int /*<<< orphan*/  thread_call_enter_delayed_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
thread_call_func_delayed_with_leeway(
	thread_call_func_t		func,
	thread_call_param_t		param,
	uint64_t		deadline,
	uint64_t		leeway,
	uint32_t		flags)
{
	(void)thread_call_enter_delayed_internal(NULL, func, param, 0, deadline, leeway, flags);
}