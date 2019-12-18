#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vfe_msg_output {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  msgOutput2; } ;
struct vfe_message {TYPE_1__ _u; int /*<<< orphan*/  _d; } ;
struct TYPE_5__ {void* ackPending; } ;
struct TYPE_6__ {scalar_t__ vstate; int vfeRequestedSnapShotCount; scalar_t__ vfeOperationMode; TYPE_2__ encPath; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 void* TRUE ; 
 int /*<<< orphan*/  VFE_MSG_ID_OUTPUT2 ; 
 scalar_t__ VFE_START_OPERATION_MODE_SNAPSHOT ; 
 scalar_t__ VFE_STATE_ACTIVE ; 
 TYPE_3__* ctrl ; 
 int /*<<< orphan*/  kfree (struct vfe_message*) ; 
 struct vfe_message* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  vfe_proc_ops (int /*<<< orphan*/ ,struct vfe_message*,int) ; 

__attribute__((used)) static void vfe_send_output2_msg(
	struct vfe_msg_output *pPayload)
{
	/* unsigned long flags; */
	struct vfe_message *msg;

	msg = kzalloc(sizeof(struct vfe_message), GFP_ATOMIC);
	if (!msg)
		return;

	/* fill message with right content. */
	/* @todo This is causing issues, need further investigate */
	/* spin_lock_irqsave(&ctrl->state_lock, flags); */
	if (ctrl->vstate != VFE_STATE_ACTIVE) {
		kfree(msg);
		goto output2_msg_done;
	}

	msg->_d = VFE_MSG_ID_OUTPUT2;

	memcpy(&(msg->_u.msgOutput2),
		(void *)pPayload, sizeof(struct vfe_msg_output));

	vfe_proc_ops(VFE_MSG_ID_OUTPUT2,
		msg, sizeof(struct vfe_message));

	ctrl->encPath.ackPending = TRUE;

	if (!(ctrl->vfeRequestedSnapShotCount <= 3) &&
			(ctrl->vfeOperationMode ==
			 VFE_START_OPERATION_MODE_SNAPSHOT))
		ctrl->encPath.ackPending = TRUE;

output2_msg_done:
	/* spin_unlock_irqrestore(&ctrl->state_lock, flags); */
	return;
}