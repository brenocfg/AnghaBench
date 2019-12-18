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
struct TYPE_3__ {int /*<<< orphan*/  tqueue; } ;
typedef  TYPE_1__ tqueue_st ;
typedef  int /*<<< orphan*/  lwpq_t ;
typedef  int /*<<< orphan*/  lwp_cntrl ;

/* Variables and functions */
 int /*<<< orphan*/  __lwp_thread_dispatchenable () ; 
 int /*<<< orphan*/ * __lwp_threadqueue_dequeue (int /*<<< orphan*/ *) ; 
 TYPE_1__* __lwp_tqueue_open (int /*<<< orphan*/ ) ; 

void LWP_ThreadBroadcast(lwpq_t thequeue)
{
	tqueue_st *tq;
	lwp_cntrl *thethread;

	tq = __lwp_tqueue_open(thequeue);
	if(!tq) return;

	do {
		thethread = __lwp_threadqueue_dequeue(&tq->tqueue);
	} while(thethread);
	__lwp_thread_dispatchenable();
}