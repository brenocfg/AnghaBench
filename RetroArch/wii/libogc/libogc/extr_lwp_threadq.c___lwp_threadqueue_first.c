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
 int /*<<< orphan*/ * __lwp_threadqueue_firstfifo (TYPE_1__*) ; 
 int /*<<< orphan*/ * __lwp_threadqueue_firstpriority (TYPE_1__*) ; 

lwp_cntrl* __lwp_threadqueue_first(lwp_thrqueue *queue)
{
	lwp_cntrl *ret;

	switch(queue->mode) {
		case LWP_THREADQ_MODEFIFO:
			ret = __lwp_threadqueue_firstfifo(queue);
			break;
		case LWP_THREADQ_MODEPRIORITY:
			ret = __lwp_threadqueue_firstpriority(queue);
			break;
		default:
			ret = NULL;
			break;
	}

	return ret;
}