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
struct TYPE_6__ {int /*<<< orphan*/  timeout; int /*<<< orphan*/  controller; int /*<<< orphan*/ * dev; } ;
struct smscore_device_t {int /*<<< orphan*/  ir_init_done; TYPE_2__ ir; } ;
struct SmsMsgHdr_ST2 {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  msgLength; } ;
struct SmsMsgData_ST2 {TYPE_4__ xMsgHeader; int /*<<< orphan*/ * msgData; } ;
struct TYPE_5__ {int ir; } ;
struct TYPE_7__ {TYPE_1__ board_cfg; } ;

/* Variables and functions */
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  MSG_SMS_START_IR_REQ ; 
 scalar_t__ SMS_ALIGN_ADDRESS (void*) ; 
 scalar_t__ SMS_DMA_ALIGNMENT ; 
 int /*<<< orphan*/  SMS_INIT_MSG (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (scalar_t__,int) ; 
 int /*<<< orphan*/  sms_err (char*) ; 
 TYPE_3__* sms_get_board (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sms_info (char*) ; 
 int sms_ir_init (struct smscore_device_t*) ; 
 int /*<<< orphan*/  smscore_get_board_id (struct smscore_device_t*) ; 
 int smscore_sendrequest_and_wait (struct smscore_device_t*,struct SmsMsgData_ST2*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smsendian_handle_tx_message (struct SmsMsgHdr_ST2*) ; 

__attribute__((used)) static int smscore_init_ir(struct smscore_device_t *coredev)
{
	int ir_io;
	int rc;
	void *buffer;

	coredev->ir.dev = NULL;
	ir_io = sms_get_board(smscore_get_board_id(coredev))->board_cfg.ir;
	if (ir_io) {/* only if IR port exist we use IR sub-module */
		sms_info("IR loading");
		rc = sms_ir_init(coredev);

		if	(rc != 0)
			sms_err("Error initialization DTV IR sub-module");
		else {
			buffer = kmalloc(sizeof(struct SmsMsgData_ST2) +
						SMS_DMA_ALIGNMENT,
						GFP_KERNEL | GFP_DMA);
			if (buffer) {
				struct SmsMsgData_ST2 *msg =
				(struct SmsMsgData_ST2 *)
				SMS_ALIGN_ADDRESS(buffer);

				SMS_INIT_MSG(&msg->xMsgHeader,
						MSG_SMS_START_IR_REQ,
						sizeof(struct SmsMsgData_ST2));
				msg->msgData[0] = coredev->ir.controller;
				msg->msgData[1] = coredev->ir.timeout;

				smsendian_handle_tx_message(
					(struct SmsMsgHdr_ST2 *)msg);
				rc = smscore_sendrequest_and_wait(coredev, msg,
						msg->xMsgHeader. msgLength,
						&coredev->ir_init_done);

				kfree(buffer);
			} else
				sms_err
				("Sending IR initialization message failed");
		}
	} else
		sms_info("IR port has not been detected");

	return 0;
}