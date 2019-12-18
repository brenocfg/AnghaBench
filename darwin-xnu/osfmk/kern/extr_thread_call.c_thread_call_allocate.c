#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_call_t ;
typedef  int /*<<< orphan*/  thread_call_param_t ;
typedef  int /*<<< orphan*/  thread_call_func_t ;
struct TYPE_5__ {int tc_refs; int /*<<< orphan*/  tc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  THREAD_CALL_ALLOC ; 
 int /*<<< orphan*/  thread_call_setup (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_call_zone ; 
 TYPE_1__* zalloc (int /*<<< orphan*/ ) ; 

thread_call_t
thread_call_allocate(
		thread_call_func_t		func,
		thread_call_param_t		param0)
{
	thread_call_t	call = zalloc(thread_call_zone);

	thread_call_setup(call, func, param0);
	call->tc_refs = 1;
	call->tc_flags = THREAD_CALL_ALLOC;

	return (call);
}