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
typedef  int /*<<< orphan*/  lwp_t ;
struct TYPE_3__ {int /*<<< orphan*/  cur_state; } ;
typedef  TYPE_1__ lwp_cntrl ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* __lwp_cntrl_open (int /*<<< orphan*/ ) ; 
 scalar_t__ __lwp_statesuspended (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_thread_dispatchenable () ; 

BOOL LWP_ThreadIsSuspended(lwp_t thethread)
{
	BOOL state;
	lwp_cntrl *lwp_thread;

	lwp_thread = __lwp_cntrl_open(thethread);
  	if(!lwp_thread) return FALSE;

	state = (__lwp_statesuspended(lwp_thread->cur_state) ? TRUE : FALSE);

	__lwp_thread_dispatchenable();
	return state;
}