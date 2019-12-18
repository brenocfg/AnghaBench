#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  tqueue; } ;
typedef  TYPE_1__ tqueue_st ;
typedef  scalar_t__ lwpq_t ;
typedef  int /*<<< orphan*/  lwp_cntrl ;

/* Variables and functions */
 int /*<<< orphan*/  __lwp_thread_dispatchenable () ; 
 int /*<<< orphan*/ * __lwp_threadqueue_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_tqueue_free (TYPE_1__*) ; 
 TYPE_1__* __lwp_tqueue_open (scalar_t__) ; 

void LWP_CloseQueue(lwpq_t thequeue)
{
	lwp_cntrl *thethread;
	tqueue_st *tq = (tqueue_st*)thequeue;

	tq = __lwp_tqueue_open(thequeue);
	if(!tq) return;

	do {
		thethread = __lwp_threadqueue_dequeue(&tq->tqueue);
	} while(thethread);
	__lwp_thread_dispatchenable();

	__lwp_tqueue_free(tq);
	return;
}