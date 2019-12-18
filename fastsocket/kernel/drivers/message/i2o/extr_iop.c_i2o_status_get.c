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
typedef  int u8 ;
struct TYPE_5__ {void* tcntxt; void* icntxt; } ;
struct TYPE_6__ {TYPE_1__ s; void** head; } ;
struct i2o_message {void** body; TYPE_2__ u; } ;
struct TYPE_7__ {int /*<<< orphan*/  phys; scalar_t__ virt; } ;
struct i2o_controller {int /*<<< orphan*/  name; TYPE_3__ status_block; } ;
typedef  int /*<<< orphan*/  i2o_status_block ;
struct TYPE_8__ {int context; } ;

/* Variables and functions */
 int ADAPTER_TID ; 
 int ETIMEDOUT ; 
 int HOST_TID ; 
 unsigned long HZ ; 
 int I2O_CMD_STATUS_GET ; 
 int /*<<< orphan*/  I2O_TIMEOUT_MESSAGE_GET ; 
 unsigned long I2O_TIMEOUT_STATUS_GET ; 
 scalar_t__ IS_ERR (struct i2o_message*) ; 
 int NINE_WORD_MSG_SIZE ; 
 int PTR_ERR (struct i2o_message*) ; 
 int SGL_OFFSET_0 ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  i2o_debug_state (struct i2o_controller*) ; 
 int i2o_dma_high (int /*<<< orphan*/ ) ; 
 int i2o_dma_low (int /*<<< orphan*/ ) ; 
 TYPE_4__ i2o_exec_driver ; 
 struct i2o_message* i2o_msg_get_wait (struct i2o_controller*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2o_msg_post (struct i2o_controller*,struct i2o_message*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  osm_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

int i2o_status_get(struct i2o_controller *c)
{
	struct i2o_message *msg;
	volatile u8 *status_block;
	unsigned long timeout;

	status_block = (u8 *) c->status_block.virt;
	memset(c->status_block.virt, 0, sizeof(i2o_status_block));

	msg = i2o_msg_get_wait(c, I2O_TIMEOUT_MESSAGE_GET);
	if (IS_ERR(msg))
		return PTR_ERR(msg);

	msg->u.head[0] = cpu_to_le32(NINE_WORD_MSG_SIZE | SGL_OFFSET_0);
	msg->u.head[1] =
	    cpu_to_le32(I2O_CMD_STATUS_GET << 24 | HOST_TID << 12 |
			ADAPTER_TID);
	msg->u.s.icntxt = cpu_to_le32(i2o_exec_driver.context);
	msg->u.s.tcntxt = cpu_to_le32(0x00000000);
	msg->body[0] = cpu_to_le32(0x00000000);
	msg->body[1] = cpu_to_le32(0x00000000);
	msg->body[2] = cpu_to_le32(i2o_dma_low(c->status_block.phys));
	msg->body[3] = cpu_to_le32(i2o_dma_high(c->status_block.phys));
	msg->body[4] = cpu_to_le32(sizeof(i2o_status_block));	/* always 88 bytes */

	i2o_msg_post(c, msg);

	/* Wait for a reply */
	timeout = jiffies + I2O_TIMEOUT_STATUS_GET * HZ;
	while (status_block[87] != 0xFF) {
		if (time_after(jiffies, timeout)) {
			osm_err("%s: Get status timeout.\n", c->name);
			return -ETIMEDOUT;
		}

		schedule_timeout_uninterruptible(1);
	}

#ifdef DEBUG
	i2o_debug_state(c);
#endif

	return 0;
}