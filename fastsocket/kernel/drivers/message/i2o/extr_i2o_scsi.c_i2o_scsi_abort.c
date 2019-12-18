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
struct scsi_cmnd {TYPE_1__* device; } ;
struct TYPE_6__ {void** head; } ;
struct i2o_message {void** body; TYPE_3__ u; } ;
struct TYPE_5__ {int tid; } ;
struct i2o_device {TYPE_2__ lct_data; struct i2o_controller* iop; } ;
struct i2o_controller {int dummy; } ;
struct TYPE_4__ {struct i2o_device* hostdata; } ;

/* Variables and functions */
 int FAILED ; 
 int FIVE_WORD_MSG_SIZE ; 
 int HOST_TID ; 
 int I2O_CMD_SCSI_ABORT ; 
 int /*<<< orphan*/  I2O_TIMEOUT_MESSAGE_GET ; 
 int /*<<< orphan*/  I2O_TIMEOUT_SCSI_SCB_ABORT ; 
 scalar_t__ IS_ERR (struct i2o_message*) ; 
 int SCSI_MLQUEUE_HOST_BUSY ; 
 int SGL_OFFSET_0 ; 
 int SUCCESS ; 
 void* cpu_to_le32 (int) ; 
 int i2o_cntxt_list_get_ptr (struct i2o_controller*,struct scsi_cmnd*) ; 
 struct i2o_message* i2o_msg_get_wait (struct i2o_controller*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2o_msg_post_wait (struct i2o_controller*,struct i2o_message*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osm_warn (char*) ; 

__attribute__((used)) static int i2o_scsi_abort(struct scsi_cmnd *SCpnt)
{
	struct i2o_device *i2o_dev;
	struct i2o_controller *c;
	struct i2o_message *msg;
	int tid;
	int status = FAILED;

	osm_warn("Aborting command block.\n");

	i2o_dev = SCpnt->device->hostdata;
	c = i2o_dev->iop;
	tid = i2o_dev->lct_data.tid;

	msg = i2o_msg_get_wait(c, I2O_TIMEOUT_MESSAGE_GET);
	if (IS_ERR(msg))
		return SCSI_MLQUEUE_HOST_BUSY;

	msg->u.head[0] = cpu_to_le32(FIVE_WORD_MSG_SIZE | SGL_OFFSET_0);
	msg->u.head[1] =
	    cpu_to_le32(I2O_CMD_SCSI_ABORT << 24 | HOST_TID << 12 | tid);
	msg->body[0] = cpu_to_le32(i2o_cntxt_list_get_ptr(c, SCpnt));

	if (!i2o_msg_post_wait(c, msg, I2O_TIMEOUT_SCSI_SCB_ABORT))
		status = SUCCESS;

	return status;
}