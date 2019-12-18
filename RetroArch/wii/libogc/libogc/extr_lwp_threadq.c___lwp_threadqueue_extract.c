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
struct TYPE_5__ {int mode; } ;
typedef  TYPE_1__ lwp_thrqueue ;
typedef  int /*<<< orphan*/  lwp_cntrl ;

/* Variables and functions */
#define  LWP_THREADQ_MODEFIFO 129 
#define  LWP_THREADQ_MODEPRIORITY 128 
 int /*<<< orphan*/  __lwp_threadqueue_extractfifo (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_threadqueue_extractpriority (TYPE_1__*,int /*<<< orphan*/ *) ; 

void __lwp_threadqueue_extract(lwp_thrqueue *queue,lwp_cntrl *thethread)
{
	switch(queue->mode) {
		case LWP_THREADQ_MODEFIFO:
			__lwp_threadqueue_extractfifo(queue,thethread);
			break;
		case LWP_THREADQ_MODEPRIORITY:
			__lwp_threadqueue_extractpriority(queue,thethread);
			break;
	}

}