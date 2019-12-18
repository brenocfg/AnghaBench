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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  mqmsg_t ;
typedef  int /*<<< orphan*/  mqbox_t ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {TYPE_1__ object; int /*<<< orphan*/  mqueue; } ;
typedef  TYPE_2__ mqbox_st ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ LWP_MQ_STATUS_SUCCESSFUL ; 
 int /*<<< orphan*/  LWP_THREADQ_NOTIMEOUT ; 
 scalar_t__ MQ_MSG_BLOCK ; 
 scalar_t__ TRUE ; 
 TYPE_2__* __lwp_mqbox_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_thread_dispatchenable () ; 
 scalar_t__ __lwpmq_seize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,scalar_t__*,scalar_t__,int /*<<< orphan*/ ) ; 

BOOL MQ_Receive(mqbox_t mqbox,mqmsg_t *msg,u32 flags)
{
	BOOL ret;
	mqbox_st *mbox;
	u32 tmp,wait = (flags==MQ_MSG_BLOCK)?TRUE:FALSE;

	mbox = __lwp_mqbox_open(mqbox);
	if(!mbox) return FALSE;

	ret = FALSE;
	if(__lwpmq_seize(&mbox->mqueue,mbox->object.id,(void*)msg,&tmp,wait,LWP_THREADQ_NOTIMEOUT)==LWP_MQ_STATUS_SUCCESSFUL) ret = TRUE;
	__lwp_thread_dispatchenable();

	return ret;
}