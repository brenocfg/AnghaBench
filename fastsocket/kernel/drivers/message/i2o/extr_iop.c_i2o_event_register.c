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
struct TYPE_5__ {void* tcntxt; void* icntxt; } ;
struct TYPE_6__ {TYPE_2__ s; void** head; } ;
struct i2o_message {void** body; TYPE_3__ u; } ;
struct i2o_driver {int context; } ;
struct TYPE_4__ {int tid; } ;
struct i2o_device {TYPE_1__ lct_data; struct i2o_controller* iop; } ;
struct i2o_controller {int dummy; } ;

/* Variables and functions */
 int FIVE_WORD_MSG_SIZE ; 
 int HOST_TID ; 
 int I2O_CMD_UTIL_EVT_REGISTER ; 
 int /*<<< orphan*/  I2O_TIMEOUT_MESSAGE_GET ; 
 scalar_t__ IS_ERR (struct i2o_message*) ; 
 int PTR_ERR (struct i2o_message*) ; 
 int SGL_OFFSET_0 ; 
 void* cpu_to_le32 (int) ; 
 struct i2o_message* i2o_msg_get_wait (struct i2o_controller*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2o_msg_post (struct i2o_controller*,struct i2o_message*) ; 

int i2o_event_register(struct i2o_device *dev, struct i2o_driver *drv,
		       int tcntxt, u32 evt_mask)
{
	struct i2o_controller *c = dev->iop;
	struct i2o_message *msg;

	msg = i2o_msg_get_wait(c, I2O_TIMEOUT_MESSAGE_GET);
	if (IS_ERR(msg))
		return PTR_ERR(msg);

	msg->u.head[0] = cpu_to_le32(FIVE_WORD_MSG_SIZE | SGL_OFFSET_0);
	msg->u.head[1] =
	    cpu_to_le32(I2O_CMD_UTIL_EVT_REGISTER << 24 | HOST_TID << 12 | dev->
			lct_data.tid);
	msg->u.s.icntxt = cpu_to_le32(drv->context);
	msg->u.s.tcntxt = cpu_to_le32(tcntxt);
	msg->body[0] = cpu_to_le32(evt_mask);

	i2o_msg_post(c, msg);

	return 0;
}