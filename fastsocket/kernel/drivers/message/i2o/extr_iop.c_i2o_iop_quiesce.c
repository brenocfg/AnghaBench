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
struct TYPE_4__ {void** head; } ;
struct i2o_message {TYPE_1__ u; } ;
struct TYPE_5__ {TYPE_3__* virt; } ;
struct i2o_controller {int /*<<< orphan*/  name; TYPE_2__ status_block; } ;
struct TYPE_6__ {scalar_t__ iop_state; } ;
typedef  TYPE_3__ i2o_status_block ;

/* Variables and functions */
 scalar_t__ ADAPTER_STATE_OPERATIONAL ; 
 scalar_t__ ADAPTER_STATE_READY ; 
 int ADAPTER_TID ; 
 int FOUR_WORD_MSG_SIZE ; 
 int HOST_TID ; 
 int I2O_CMD_SYS_QUIESCE ; 
 int /*<<< orphan*/  I2O_TIMEOUT_MESSAGE_GET ; 
 scalar_t__ IS_ERR (struct i2o_message*) ; 
 int PTR_ERR (struct i2o_message*) ; 
 int SGL_OFFSET_0 ; 
 void* cpu_to_le32 (int) ; 
 struct i2o_message* i2o_msg_get_wait (struct i2o_controller*,int /*<<< orphan*/ ) ; 
 int i2o_msg_post_wait (struct i2o_controller*,struct i2o_message*,int) ; 
 int /*<<< orphan*/  i2o_status_get (struct i2o_controller*) ; 
 int /*<<< orphan*/  osm_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osm_info (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int i2o_iop_quiesce(struct i2o_controller *c)
{
	struct i2o_message *msg;
	i2o_status_block *sb = c->status_block.virt;
	int rc;

	i2o_status_get(c);

	/* SysQuiesce discarded if IOP not in READY or OPERATIONAL state */
	if ((sb->iop_state != ADAPTER_STATE_READY) &&
	    (sb->iop_state != ADAPTER_STATE_OPERATIONAL))
		return 0;

	msg = i2o_msg_get_wait(c, I2O_TIMEOUT_MESSAGE_GET);
	if (IS_ERR(msg))
		return PTR_ERR(msg);

	msg->u.head[0] = cpu_to_le32(FOUR_WORD_MSG_SIZE | SGL_OFFSET_0);
	msg->u.head[1] =
	    cpu_to_le32(I2O_CMD_SYS_QUIESCE << 24 | HOST_TID << 12 |
			ADAPTER_TID);

	/* Long timeout needed for quiesce if lots of devices */
	if ((rc = i2o_msg_post_wait(c, msg, 240)))
		osm_info("%s: Unable to quiesce (status=%#x).\n", c->name, -rc);
	else
		osm_debug("%s: Quiesced.\n", c->name);

	i2o_status_get(c);	// Entered READY state

	return rc;
}