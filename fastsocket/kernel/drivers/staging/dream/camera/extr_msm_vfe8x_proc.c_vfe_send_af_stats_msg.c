#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  frameCounter; int /*<<< orphan*/  afBuffer; } ;
struct TYPE_7__ {TYPE_2__ msgStatsAf; } ;
struct vfe_message {TYPE_3__ _u; int /*<<< orphan*/  _d; } ;
struct TYPE_5__ {int /*<<< orphan*/  ackPending; } ;
struct TYPE_8__ {scalar_t__ vstate; TYPE_1__ afStatsControl; int /*<<< orphan*/  vfeFrameId; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VFE_MSG_ID_STATS_AUTOFOCUS ; 
 scalar_t__ VFE_STATE_ACTIVE ; 
 TYPE_4__* ctrl ; 
 int /*<<< orphan*/  kfree (struct vfe_message*) ; 
 struct vfe_message* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfe_proc_ops (int /*<<< orphan*/ ,struct vfe_message*,int) ; 

__attribute__((used)) static void
vfe_send_af_stats_msg(uint32_t afBufAddress)
{
	/* unsigned long flags; */
	struct vfe_message *msg;
	msg =
		kzalloc(sizeof(struct vfe_message), GFP_ATOMIC);
	if (!msg)
		return;

	/* fill message with right content. */
	/* @todo This is causing issues, need further investigate */
	/* spin_lock_irqsave(&ctrl->state_lock, flags); */
	if (ctrl->vstate != VFE_STATE_ACTIVE) {
		kfree(msg);
		goto af_stats_done;
	}

	msg->_d = VFE_MSG_ID_STATS_AUTOFOCUS;
	msg->_u.msgStatsAf.afBuffer = afBufAddress;
	msg->_u.msgStatsAf.frameCounter = ctrl->vfeFrameId;

	vfe_proc_ops(VFE_MSG_ID_STATS_AUTOFOCUS,
		msg, sizeof(struct vfe_message));

	ctrl->afStatsControl.ackPending = TRUE;

af_stats_done:
	/* spin_unlock_irqrestore(&ctrl->state_lock, flags); */
	return;
}