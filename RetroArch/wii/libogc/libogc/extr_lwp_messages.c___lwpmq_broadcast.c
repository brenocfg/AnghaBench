#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {scalar_t__ num_pendingmsgs; int max_msgsize; int /*<<< orphan*/  wait_queue; } ;
typedef  TYPE_1__ mq_cntrl ;
struct TYPE_8__ {scalar_t__ ret_arg_1; int /*<<< orphan*/  ret_arg; } ;
typedef  TYPE_2__ lwp_waitinfo ;
struct TYPE_9__ {TYPE_2__ wait; } ;
typedef  TYPE_3__ lwp_cntrl ;

/* Variables and functions */
 int LWP_MQ_STATUS_SUCCESSFUL ; 
 TYPE_3__* __lwp_threadqueue_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwpmq_buffer_copy (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  printf (char*,TYPE_1__*,void*,int,int,int*) ; 

u32 __lwpmq_broadcast(mq_cntrl *mqueue,void *buffer,u32 size,u32 id,u32 *count)
{
	lwp_cntrl *thread;
	u32 num_broadcast;
	lwp_waitinfo *waitp;
	u32 rsize;
#ifdef _LWPMQ_DEBUG
	printf("__lwpmq_broadcast(%p,%p,%d,%d,%p)\n",mqueue,buffer,size,id,count);
#endif
	if(mqueue->num_pendingmsgs!=0) {
		*count = 0;
		return LWP_MQ_STATUS_SUCCESSFUL;
	}

	num_broadcast = 0;
	while((thread=__lwp_threadqueue_dequeue(&mqueue->wait_queue))) {
		waitp = &thread->wait;
		++num_broadcast;

		rsize = size;
		if(size>mqueue->max_msgsize)
			rsize = mqueue->max_msgsize;

		__lwpmq_buffer_copy(waitp->ret_arg,buffer,rsize);
		*(u32*)waitp->ret_arg_1 = size;
	}
	*count = num_broadcast;
	return LWP_MQ_STATUS_SUCCESSFUL;
}