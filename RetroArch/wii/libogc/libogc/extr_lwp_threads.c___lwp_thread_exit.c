#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/ * ret_arg; } ;
struct TYPE_5__ {TYPE_1__ wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  __lwp_thread_close (TYPE_2__*) ; 
 int /*<<< orphan*/  __lwp_thread_dispatchdisable () ; 
 int /*<<< orphan*/  __lwp_thread_dispatchenable () ; 
 TYPE_2__* _thr_executing ; 

void __lwp_thread_exit(void *value_ptr)
{
	__lwp_thread_dispatchdisable();
	_thr_executing->wait.ret_arg = (u32*)value_ptr;
	__lwp_thread_close(_thr_executing);
	__lwp_thread_dispatchenable();
}