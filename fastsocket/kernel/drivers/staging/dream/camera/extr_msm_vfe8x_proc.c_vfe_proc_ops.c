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
struct TYPE_4__ {int msg_id; size_t len; void* data; int /*<<< orphan*/  type; } ;
struct msm_vfe_resp {void* type; TYPE_1__ evt_msg; int /*<<< orphan*/  phy; int /*<<< orphan*/  extlen; int /*<<< orphan*/  extdata; } ;
typedef  enum VFE_MESSAGE_ID { ____Placeholder_VFE_MESSAGE_ID } VFE_MESSAGE_ID ;
struct TYPE_6__ {scalar_t__ vfeOperationMode; int /*<<< orphan*/  syncdata; TYPE_2__* resp; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* vfe_resp ) (struct msm_vfe_resp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;struct msm_vfe_resp* (* vfe_alloc ) (int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CDBG (char*,...) ; 
 int /*<<< orphan*/  MSM_CAMERA_MSG ; 
 int /*<<< orphan*/  MSM_CAM_Q_VFE_MSG ; 
 void* VFE_MSG_GENERAL ; 
#define  VFE_MSG_ID_OUTPUT1 132 
#define  VFE_MSG_ID_OUTPUT2 131 
#define  VFE_MSG_ID_SNAPSHOT_DONE 130 
#define  VFE_MSG_ID_STATS_AUTOFOCUS 129 
#define  VFE_MSG_ID_STATS_WB_EXP 128 
 void* VFE_MSG_OUTPUT1 ; 
 void* VFE_MSG_OUTPUT2 ; 
 void* VFE_MSG_SNAPSHOT ; 
 void* VFE_MSG_STATS_AF ; 
 void* VFE_MSG_STATS_WE ; 
 scalar_t__ VFE_START_OPERATION_MODE_SNAPSHOT ; 
 TYPE_3__* ctrl ; 
 struct msm_vfe_resp* stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct msm_vfe_resp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfe_addr_convert (int /*<<< orphan*/ *,void*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vfe_proc_ops(enum VFE_MESSAGE_ID id, void *msg, size_t len)
{
	struct msm_vfe_resp *rp;

	/* In 8k, OUTPUT1 & OUTPUT2 messages arrive before
	 * SNAPSHOT_DONE. We don't send such messages to user */

	CDBG("ctrl->vfeOperationMode = %d, msgId = %d\n",
		ctrl->vfeOperationMode, id);

	if ((ctrl->vfeOperationMode == VFE_START_OPERATION_MODE_SNAPSHOT) &&
		(id == VFE_MSG_ID_OUTPUT1 || id == VFE_MSG_ID_OUTPUT2)) {
		return;
	}

	rp = ctrl->resp->vfe_alloc(sizeof(struct msm_vfe_resp), ctrl->syncdata);
	if (!rp) {
		CDBG("rp: cannot allocate buffer\n");
		return;
	}

	CDBG("vfe_proc_ops, msgId = %d\n", id);

	rp->evt_msg.type   = MSM_CAMERA_MSG;
	rp->evt_msg.msg_id = id;
	rp->evt_msg.len    = len;
	rp->evt_msg.data   = msg;

	switch (rp->evt_msg.msg_id) {
	case VFE_MSG_ID_SNAPSHOT_DONE:
		rp->type = VFE_MSG_SNAPSHOT;
		break;

	case VFE_MSG_ID_OUTPUT1:
		rp->type = VFE_MSG_OUTPUT1;
		vfe_addr_convert(&(rp->phy), VFE_MSG_OUTPUT1,
			rp->evt_msg.data, &(rp->extdata),
			&(rp->extlen));
		break;

	case VFE_MSG_ID_OUTPUT2:
		rp->type = VFE_MSG_OUTPUT2;
		vfe_addr_convert(&(rp->phy), VFE_MSG_OUTPUT2,
				rp->evt_msg.data, &(rp->extdata),
				&(rp->extlen));
		break;

	case VFE_MSG_ID_STATS_AUTOFOCUS:
		rp->type = VFE_MSG_STATS_AF;
		vfe_addr_convert(&(rp->phy), VFE_MSG_STATS_AF,
				rp->evt_msg.data, NULL, NULL);
		break;

	case VFE_MSG_ID_STATS_WB_EXP:
		rp->type = VFE_MSG_STATS_WE;
		vfe_addr_convert(&(rp->phy), VFE_MSG_STATS_WE,
				rp->evt_msg.data, NULL, NULL);
		break;

	default:
		rp->type = VFE_MSG_GENERAL;
		break;
	}

	ctrl->resp->vfe_resp(rp, MSM_CAM_Q_VFE_MSG, ctrl->syncdata);
}