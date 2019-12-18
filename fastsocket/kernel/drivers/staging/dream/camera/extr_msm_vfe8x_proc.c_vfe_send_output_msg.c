#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  redBlueDefectPixelCount; int /*<<< orphan*/  greenDefectPixelCount; } ;
struct TYPE_9__ {int /*<<< orphan*/  asfMaxEdge; int /*<<< orphan*/  asfHbiCount; } ;
struct vfe_msg_output {int /*<<< orphan*/  frameCounter; TYPE_2__ bpcInfo; TYPE_4__ asfInfo; void* cbcrBuffer; void* yBuffer; } ;
typedef  scalar_t__ boolean ;
struct TYPE_8__ {int /*<<< orphan*/  redBlueDefectPixelCount; int /*<<< orphan*/  greenDefectPixelCount; } ;
struct TYPE_6__ {int /*<<< orphan*/  asfMaxEdge; int /*<<< orphan*/  asfHbiCount; } ;
struct TYPE_10__ {int /*<<< orphan*/  vfeFrameId; TYPE_3__ vfeBpcFrameInfo; TYPE_1__ vfeAsfFrameInfo; } ;

/* Variables and functions */
 TYPE_5__* ctrl ; 
 int /*<<< orphan*/  vfe_send_output1_msg (struct vfe_msg_output*) ; 
 int /*<<< orphan*/  vfe_send_output2_msg (struct vfe_msg_output*) ; 

__attribute__((used)) static void vfe_send_output_msg(boolean whichOutputPath,
	uint32_t yPathAddr, uint32_t cbcrPathAddr)
{
	struct vfe_msg_output msgPayload;

	msgPayload.yBuffer = yPathAddr;
	msgPayload.cbcrBuffer = cbcrPathAddr;

	/* asf info is common for both output1 and output2 */
#if 0
	msgPayload.asfInfo.asfHbiCount = ctrl->vfeAsfFrameInfo.asfHbiCount;
	msgPayload.asfInfo.asfMaxEdge = ctrl->vfeAsfFrameInfo.asfMaxEdge;

	/* demosaic info is common for both output1 and output2 */
	msgPayload.bpcInfo.greenDefectPixelCount =
		ctrl->vfeBpcFrameInfo.greenDefectPixelCount;
	msgPayload.bpcInfo.redBlueDefectPixelCount =
		ctrl->vfeBpcFrameInfo.redBlueDefectPixelCount;
#endif /* if 0 */

	/* frame ID is common for both paths. */
	msgPayload.frameCounter = ctrl->vfeFrameId;

	if (whichOutputPath) {
		/* msgPayload.pmData = ctrl->vfePmData.encPathPmInfo; */
		vfe_send_output2_msg(&msgPayload);
	} else {
		/* msgPayload.pmData = ctrl->vfePmData.viewPathPmInfo; */
		vfe_send_output1_msg(&msgPayload);
	}
}