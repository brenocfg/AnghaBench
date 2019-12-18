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
typedef  int u32 ;
struct TYPE_5__ {int max_pendingmsgs; int max_msgsize; int /*<<< orphan*/  wait_queue; int /*<<< orphan*/  pending_msgs; int /*<<< orphan*/ * msq_buffers; int /*<<< orphan*/  inactive_msgs; scalar_t__ num_pendingmsgs; } ;
typedef  TYPE_1__ mq_cntrl ;
typedef  int /*<<< orphan*/  mq_buffercntrl ;
typedef  int /*<<< orphan*/  mq_buffer ;
typedef  int /*<<< orphan*/  mq_attr ;

/* Variables and functions */
 int /*<<< orphan*/  LWP_MQ_STATUS_TIMEOUT ; 
 int /*<<< orphan*/  LWP_STATES_WAITING_FOR_MESSAGE ; 
 int /*<<< orphan*/  LWP_THREADQ_MODEFIFO ; 
 int /*<<< orphan*/  LWP_THREADQ_MODEPRIORITY ; 
 int /*<<< orphan*/  __lwp_queue_init_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_queue_initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  __lwp_threadqueue_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __lwp_wkspace_allocate (int) ; 
 scalar_t__ __lwpmq_is_priority (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwpmq_set_notify (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,TYPE_1__*,int /*<<< orphan*/ *,int,int) ; 

u32 __lwpmq_initialize(mq_cntrl *mqueue,mq_attr *attrs,u32 max_pendingmsgs,u32 max_msgsize)
{
	u32 alloc_msgsize;
	u32 buffering_req;

#ifdef _LWPMQ_DEBUG
	printf("__lwpmq_initialize(%p,%p,%d,%d)\n",mqueue,attrs,max_pendingmsgs,max_msgsize);
#endif
	mqueue->max_pendingmsgs = max_pendingmsgs;
	mqueue->num_pendingmsgs = 0;
	mqueue->max_msgsize = max_msgsize;
	__lwpmq_set_notify(mqueue,NULL,NULL);

	alloc_msgsize = max_msgsize;
	if(alloc_msgsize&(sizeof(u32)-1))
		alloc_msgsize = (alloc_msgsize+sizeof(u32))&~(sizeof(u32)-1);

	buffering_req = max_pendingmsgs*(alloc_msgsize+sizeof(mq_buffercntrl));
	mqueue->msq_buffers = (mq_buffer*)__lwp_wkspace_allocate(buffering_req);

	if(!mqueue->msq_buffers) return 0;

	__lwp_queue_initialize(&mqueue->inactive_msgs,mqueue->msq_buffers,max_pendingmsgs,(alloc_msgsize+sizeof(mq_buffercntrl)));
	__lwp_queue_init_empty(&mqueue->pending_msgs);
	__lwp_threadqueue_init(&mqueue->wait_queue,__lwpmq_is_priority(attrs)?LWP_THREADQ_MODEPRIORITY:LWP_THREADQ_MODEFIFO,LWP_STATES_WAITING_FOR_MESSAGE,LWP_MQ_STATUS_TIMEOUT);

	return 1;
}