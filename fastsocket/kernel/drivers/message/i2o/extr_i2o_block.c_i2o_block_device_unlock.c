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
typedef  int u32 ;
struct TYPE_4__ {void** head; } ;
struct i2o_message {void** body; TYPE_2__ u; } ;
struct TYPE_3__ {int tid; } ;
struct i2o_device {int /*<<< orphan*/  iop; TYPE_1__ lct_data; } ;

/* Variables and functions */
 int FIVE_WORD_MSG_SIZE ; 
 int HOST_TID ; 
 int I2O_CMD_BLOCK_MUNLOCK ; 
 int /*<<< orphan*/  I2O_TIMEOUT_MESSAGE_GET ; 
 scalar_t__ IS_ERR (struct i2o_message*) ; 
 int PTR_ERR (struct i2o_message*) ; 
 int SGL_OFFSET_0 ; 
 void* cpu_to_le32 (int) ; 
 struct i2o_message* i2o_msg_get_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2o_msg_post_wait (int /*<<< orphan*/ ,struct i2o_message*,int) ; 
 int /*<<< orphan*/  osm_debug (char*) ; 

__attribute__((used)) static int i2o_block_device_unlock(struct i2o_device *dev, u32 media_id)
{
	struct i2o_message *msg;

	msg = i2o_msg_get_wait(dev->iop, I2O_TIMEOUT_MESSAGE_GET);
	if (IS_ERR(msg))
		return PTR_ERR(msg);

	msg->u.head[0] = cpu_to_le32(FIVE_WORD_MSG_SIZE | SGL_OFFSET_0);
	msg->u.head[1] =
	    cpu_to_le32(I2O_CMD_BLOCK_MUNLOCK << 24 | HOST_TID << 12 | dev->
			lct_data.tid);
	msg->body[0] = cpu_to_le32(media_id);
	osm_debug("Unlocking...\n");

	return i2o_msg_post_wait(dev->iop, msg, 2);
}