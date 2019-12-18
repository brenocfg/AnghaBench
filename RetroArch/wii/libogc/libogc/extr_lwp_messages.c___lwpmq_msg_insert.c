#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_17__ {TYPE_4__* first; } ;
struct TYPE_15__ {int num_pendingmsgs; int /*<<< orphan*/  notify_arg; int /*<<< orphan*/  (* notify_handler ) (int /*<<< orphan*/ ) ;TYPE_3__ pending_msgs; } ;
typedef  TYPE_1__ mq_cntrl ;
struct TYPE_16__ {int prio; int /*<<< orphan*/  node; } ;
typedef  TYPE_2__ mq_buffercntrl ;
typedef  TYPE_3__ lwp_queue ;
struct TYPE_18__ {int /*<<< orphan*/  prev; struct TYPE_18__* next; } ;
typedef  TYPE_4__ lwp_node ;

/* Variables and functions */
#define  LWP_MQ_SEND_REQUEST 129 
#define  LWP_MQ_SEND_URGENT 128 
 int /*<<< orphan*/  __lwp_queue_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_queue_istail (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  __lwpmq_msg_append (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  __lwpmq_msg_prepend (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  printf (char*,TYPE_1__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void __lwpmq_msg_insert(mq_cntrl *mqueue,mq_buffercntrl *msg,u32 type)
{
	++mqueue->num_pendingmsgs;
	msg->prio = type;

#ifdef _LWPMQ_DEBUG
	printf("__lwpmq_msg_insert(%p,%p,%d)\n",mqueue,msg,type);
#endif

	switch(type) {
		case LWP_MQ_SEND_REQUEST:
			__lwpmq_msg_append(mqueue,msg);
			break;
		case LWP_MQ_SEND_URGENT:
			__lwpmq_msg_prepend(mqueue,msg);
			break;
		default:
		{
			mq_buffercntrl *tmsg;
			lwp_node *node;
			lwp_queue *header;

			header = &mqueue->pending_msgs;
			node = header->first;
			while(!__lwp_queue_istail(header,node)) {
				tmsg = (mq_buffercntrl*)node;
				if(tmsg->prio<=msg->prio) {
					node = node->next;
					continue;
				}
				break;
			}
			__lwp_queue_insert(node->prev,&msg->node);
		}
		break;
	}

	if(mqueue->num_pendingmsgs==1 && mqueue->notify_handler)
		mqueue->notify_handler(mqueue->notify_arg);
}