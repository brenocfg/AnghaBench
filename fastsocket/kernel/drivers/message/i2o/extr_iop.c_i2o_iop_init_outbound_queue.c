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
typedef  scalar_t__ ulong ;
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_6__ {void* tcntxt; void* icntxt; } ;
struct TYPE_7__ {TYPE_1__ s; void** head; } ;
struct i2o_message {void** body; TYPE_2__ u; } ;
struct TYPE_9__ {int phys; } ;
struct TYPE_8__ {scalar_t__* virt; int /*<<< orphan*/  phys; } ;
struct i2o_controller {TYPE_4__ out_queue; int /*<<< orphan*/  name; TYPE_3__ status; } ;
struct TYPE_10__ {int context; } ;

/* Variables and functions */
 int ADAPTER_TID ; 
 int EIGHT_WORD_MSG_SIZE ; 
 int ETIMEDOUT ; 
 int HOST_TID ; 
 int HZ ; 
 scalar_t__ volatile I2O_CMD_IN_PROGRESS ; 
 int I2O_CMD_OUTBOUND_INIT ; 
 int I2O_MAX_OUTBOUND_MSG_FRAMES ; 
 int I2O_OUTBOUND_MSG_FRAME_SIZE ; 
 int I2O_TIMEOUT_INIT_OUTBOUND_QUEUE ; 
 int /*<<< orphan*/  I2O_TIMEOUT_MESSAGE_GET ; 
 scalar_t__ IS_ERR (struct i2o_message*) ; 
 int PAGE_SIZE ; 
 int PTR_ERR (struct i2o_message*) ; 
 int SGL_OFFSET_6 ; 
 void* cpu_to_le32 (int) ; 
 int i2o_dma_high (int /*<<< orphan*/ ) ; 
 int i2o_dma_low (int /*<<< orphan*/ ) ; 
 TYPE_5__ i2o_exec_driver ; 
 int /*<<< orphan*/  i2o_flush_reply (struct i2o_controller*,int) ; 
 struct i2o_message* i2o_msg_get_wait (struct i2o_controller*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2o_msg_post (struct i2o_controller*,struct i2o_message*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  osm_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osm_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int i2o_iop_init_outbound_queue(struct i2o_controller *c)
{
	u32 m;
	volatile u8 *status = c->status.virt;
	struct i2o_message *msg;
	ulong timeout;
	int i;

	osm_debug("%s: Initializing Outbound Queue...\n", c->name);

	memset(c->status.virt, 0, 4);

	msg = i2o_msg_get_wait(c, I2O_TIMEOUT_MESSAGE_GET);
	if (IS_ERR(msg))
		return PTR_ERR(msg);

	msg->u.head[0] = cpu_to_le32(EIGHT_WORD_MSG_SIZE | SGL_OFFSET_6);
	msg->u.head[1] =
	    cpu_to_le32(I2O_CMD_OUTBOUND_INIT << 24 | HOST_TID << 12 |
			ADAPTER_TID);
	msg->u.s.icntxt = cpu_to_le32(i2o_exec_driver.context);
	msg->u.s.tcntxt = cpu_to_le32(0x00000000);
	msg->body[0] = cpu_to_le32(PAGE_SIZE);
	/* Outbound msg frame size in words and Initcode */
	msg->body[1] = cpu_to_le32(I2O_OUTBOUND_MSG_FRAME_SIZE << 16 | 0x80);
	msg->body[2] = cpu_to_le32(0xd0000004);
	msg->body[3] = cpu_to_le32(i2o_dma_low(c->status.phys));
	msg->body[4] = cpu_to_le32(i2o_dma_high(c->status.phys));

	i2o_msg_post(c, msg);

	timeout = jiffies + I2O_TIMEOUT_INIT_OUTBOUND_QUEUE * HZ;
	while (*status <= I2O_CMD_IN_PROGRESS) {
		if (time_after(jiffies, timeout)) {
			osm_warn("%s: Timeout Initializing\n", c->name);
			return -ETIMEDOUT;
		}
		schedule_timeout_uninterruptible(1);
	}

	m = c->out_queue.phys;

	/* Post frames */
	for (i = 0; i < I2O_MAX_OUTBOUND_MSG_FRAMES; i++) {
		i2o_flush_reply(c, m);
		udelay(1);	/* Promise */
		m += I2O_OUTBOUND_MSG_FRAME_SIZE * sizeof(u32);
	}

	return 0;
}