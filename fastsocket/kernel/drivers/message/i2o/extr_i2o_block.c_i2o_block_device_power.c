#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {void** head; } ;
struct i2o_message {void** body; TYPE_1__ u; } ;
struct TYPE_4__ {int tid; } ;
struct i2o_device {TYPE_2__ lct_data; struct i2o_controller* iop; } ;
struct i2o_controller {int dummy; } ;
struct i2o_block_device {int power; struct i2o_device* i2o_dev; } ;

/* Variables and functions */
 int FOUR_WORD_MSG_SIZE ; 
 int HOST_TID ; 
 int I2O_CMD_BLOCK_POWER ; 
 int /*<<< orphan*/  I2O_TIMEOUT_MESSAGE_GET ; 
 scalar_t__ IS_ERR (struct i2o_message*) ; 
 int PTR_ERR (struct i2o_message*) ; 
 int SGL_OFFSET_0 ; 
 void* cpu_to_le32 (int) ; 
 struct i2o_message* i2o_msg_get_wait (struct i2o_controller*,int /*<<< orphan*/ ) ; 
 int i2o_msg_post_wait (struct i2o_controller*,struct i2o_message*,int) ; 
 int /*<<< orphan*/  osm_debug (char*) ; 

__attribute__((used)) static int i2o_block_device_power(struct i2o_block_device *dev, u8 op)
{
	struct i2o_device *i2o_dev = dev->i2o_dev;
	struct i2o_controller *c = i2o_dev->iop;
	struct i2o_message *msg;
	int rc;

	msg = i2o_msg_get_wait(c, I2O_TIMEOUT_MESSAGE_GET);
	if (IS_ERR(msg))
		return PTR_ERR(msg);

	msg->u.head[0] = cpu_to_le32(FOUR_WORD_MSG_SIZE | SGL_OFFSET_0);
	msg->u.head[1] =
	    cpu_to_le32(I2O_CMD_BLOCK_POWER << 24 | HOST_TID << 12 | i2o_dev->
			lct_data.tid);
	msg->body[0] = cpu_to_le32(op << 24);
	osm_debug("Power...\n");

	rc = i2o_msg_post_wait(c, msg, 60);
	if (!rc)
		dev->power = op;

	return rc;
}