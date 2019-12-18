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
typedef  TYPE_1__* timer_call_t ;
typedef  int /*<<< orphan*/  timer_call_param_t ;
typedef  int /*<<< orphan*/  timer_call_func_t ;
struct TYPE_5__ {int /*<<< orphan*/  async_dequeue; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TCE (TYPE_1__*) ; 
 int /*<<< orphan*/  call_entry_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_lock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
timer_call_setup(
	timer_call_t			call,
	timer_call_func_t		func,
	timer_call_param_t		param0)
{
	DBG("timer_call_setup(%p,%p,%p)\n", call, func, param0);
	call_entry_setup(TCE(call), func, param0);
	simple_lock_init(&(call)->lock, 0);
	call->async_dequeue = FALSE;
}