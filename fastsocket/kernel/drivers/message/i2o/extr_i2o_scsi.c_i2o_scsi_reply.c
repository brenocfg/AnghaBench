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
typedef  int u32 ;
struct scsi_cmnd {int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;int /*<<< orphan*/  sense_buffer; int /*<<< orphan*/  serial_number; } ;
struct TYPE_4__ {int /*<<< orphan*/  tcntxt; } ;
struct TYPE_5__ {TYPE_1__ s; } ;
struct i2o_message {int /*<<< orphan*/ * body; TYPE_2__ u; } ;
struct i2o_controller {TYPE_3__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_6__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 struct scsi_cmnd* i2o_cntxt_list_get (struct i2o_controller*,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  osm_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osm_err (char*,...) ; 
 int /*<<< orphan*/  scsi_dma_unmap (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int i2o_scsi_reply(struct i2o_controller *c, u32 m,
			  struct i2o_message *msg)
{
	struct scsi_cmnd *cmd;
	u32 error;
	struct device *dev;

	cmd = i2o_cntxt_list_get(c, le32_to_cpu(msg->u.s.tcntxt));
	if (unlikely(!cmd)) {
		osm_err("NULL reply received!\n");
		return -1;
	}

	/*
	 *      Low byte is device status, next is adapter status,
	 *      (then one byte reserved), then request status.
	 */
	error = le32_to_cpu(msg->body[0]);

	osm_debug("Completed %ld\n", cmd->serial_number);

	cmd->result = error & 0xff;
	/*
	 * if DeviceStatus is not SCSI_SUCCESS copy over the sense data and let
	 * the SCSI layer handle the error
	 */
	if (cmd->result)
		memcpy(cmd->sense_buffer, &msg->body[3],
		       min(SCSI_SENSE_BUFFERSIZE, 40));

	/* only output error code if AdapterStatus is not HBA_SUCCESS */
	if ((error >> 8) & 0xff)
		osm_err("SCSI error %08x\n", error);

	dev = &c->pdev->dev;

	scsi_dma_unmap(cmd);

	cmd->scsi_done(cmd);

	return 1;
}