#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ vfeStartAckPendingFlag; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDBG (char*,scalar_t__) ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VFE_MSG_ID_START_ACK ; 
 int /*<<< orphan*/  VFE_MSG_ID_UPDATE_ACK ; 
 TYPE_1__* ctrl ; 
 int /*<<< orphan*/  vfe_send_msg_no_payload (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vfe_process_reg_update_irq(void)
{
	CDBG("vfe_process_reg_update_irq: ackPendingFlag is %d\n",
	ctrl->vfeStartAckPendingFlag);
	if (ctrl->vfeStartAckPendingFlag == TRUE) {
		vfe_send_msg_no_payload(VFE_MSG_ID_START_ACK);
		ctrl->vfeStartAckPendingFlag = FALSE;
	} else
		vfe_send_msg_no_payload(VFE_MSG_ID_UPDATE_ACK);
}