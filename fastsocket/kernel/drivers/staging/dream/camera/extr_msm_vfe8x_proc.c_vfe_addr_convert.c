#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  awbBuffer; } ;
struct TYPE_9__ {int /*<<< orphan*/  afBuffer; } ;
struct TYPE_8__ {int /*<<< orphan*/  pmData; int /*<<< orphan*/  frameCounter; int /*<<< orphan*/  asfInfo; int /*<<< orphan*/  bpcInfo; int /*<<< orphan*/  cbcrBuffer; int /*<<< orphan*/  yBuffer; } ;
struct TYPE_7__ {int /*<<< orphan*/  pmData; int /*<<< orphan*/  frameCounter; int /*<<< orphan*/  asfInfo; int /*<<< orphan*/  bpcInfo; int /*<<< orphan*/  cbcrBuffer; int /*<<< orphan*/  yBuffer; } ;
struct TYPE_11__ {TYPE_4__ msgStatsWbExp; TYPE_3__ msgStatsAf; TYPE_2__ msgOutput2; TYPE_1__ msgOutput1; } ;
struct vfe_message {TYPE_5__ _u; } ;
struct vfe_frame_extra {int /*<<< orphan*/  pmData; int /*<<< orphan*/  frameCounter; int /*<<< orphan*/  asfInfo; int /*<<< orphan*/  bpcInfo; } ;
struct msm_vfe_phy_info {int /*<<< orphan*/  sbuf_phy; int /*<<< orphan*/  cbcr_phy; int /*<<< orphan*/  y_phy; } ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  enum vfe_resp_msg { ____Placeholder_vfe_resp_msg } vfe_resp_msg ;
struct TYPE_12__ {int /*<<< orphan*/  extlen; void* extdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDBG (char*,int /*<<< orphan*/ ) ; 
#define  VFE_MSG_OUTPUT1 131 
#define  VFE_MSG_OUTPUT2 130 
#define  VFE_MSG_STATS_AF 129 
#define  VFE_MSG_STATS_WE 128 
 TYPE_6__* ctrl ; 

__attribute__((used)) static void vfe_addr_convert(struct msm_vfe_phy_info *pinfo,
	enum vfe_resp_msg type, void *data, void **ext, int32_t *elen)
{
	switch (type) {
	case VFE_MSG_OUTPUT1: {
		pinfo->y_phy =
			((struct vfe_message *)data)->_u.msgOutput1.yBuffer;
		pinfo->cbcr_phy =
			((struct vfe_message *)data)->_u.msgOutput1.cbcrBuffer;

		((struct vfe_frame_extra *)ctrl->extdata)->bpcInfo =
		((struct vfe_message *)data)->_u.msgOutput1.bpcInfo;

		((struct vfe_frame_extra *)ctrl->extdata)->asfInfo =
		((struct vfe_message *)data)->_u.msgOutput1.asfInfo;

		((struct vfe_frame_extra *)ctrl->extdata)->frameCounter =
		((struct vfe_message *)data)->_u.msgOutput1.frameCounter;

		((struct vfe_frame_extra *)ctrl->extdata)->pmData =
		((struct vfe_message *)data)->_u.msgOutput1.pmData;

		*ext  = ctrl->extdata;
		*elen = ctrl->extlen;
	}
		break;

	case VFE_MSG_OUTPUT2: {
		pinfo->y_phy =
			((struct vfe_message *)data)->_u.msgOutput2.yBuffer;
		pinfo->cbcr_phy =
			((struct vfe_message *)data)->_u.msgOutput2.cbcrBuffer;

		CDBG("vfe_addr_convert, pinfo->y_phy = 0x%x\n", pinfo->y_phy);
		CDBG("vfe_addr_convert, pinfo->cbcr_phy = 0x%x\n",
			pinfo->cbcr_phy);

		((struct vfe_frame_extra *)ctrl->extdata)->bpcInfo =
		((struct vfe_message *)data)->_u.msgOutput2.bpcInfo;

		((struct vfe_frame_extra *)ctrl->extdata)->asfInfo =
		((struct vfe_message *)data)->_u.msgOutput2.asfInfo;

		((struct vfe_frame_extra *)ctrl->extdata)->frameCounter =
		((struct vfe_message *)data)->_u.msgOutput2.frameCounter;

		((struct vfe_frame_extra *)ctrl->extdata)->pmData =
		((struct vfe_message *)data)->_u.msgOutput2.pmData;

		*ext  = ctrl->extdata;
		*elen = ctrl->extlen;
	}
		break;

	case VFE_MSG_STATS_AF:
		pinfo->sbuf_phy =
		((struct vfe_message *)data)->_u.msgStatsAf.afBuffer;
		break;

	case VFE_MSG_STATS_WE:
		pinfo->sbuf_phy =
		((struct vfe_message *)data)->_u.msgStatsWbExp.awbBuffer;
		break;

	default:
		break;
	} /* switch */
}