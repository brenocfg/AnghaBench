#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int /*<<< orphan*/  queue; } ;
struct TYPE_6__ {TYPE_1__ wait; int /*<<< orphan*/  cur_state; } ;
typedef  TYPE_2__ lwp_cntrl ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ __lwp_statewaitthreadqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_threadqueue_extract (int /*<<< orphan*/ ,TYPE_2__*) ; 

u32 __lwp_threadqueue_extractproxy(lwp_cntrl *thethread)
{
	u32 state;

	state = thethread->cur_state;
	if(__lwp_statewaitthreadqueue(state)) {
		__lwp_threadqueue_extract(thethread->wait.queue,thethread);
		return TRUE;
	}
	return FALSE;
}