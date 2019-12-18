#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_9__ {void* tcntxt; void* icntxt; } ;
struct TYPE_10__ {TYPE_2__ s; void** head; } ;
struct i2o_message {void** body; TYPE_3__ u; } ;
struct TYPE_11__ {int* virt; int /*<<< orphan*/  phys; } ;
struct TYPE_8__ {TYPE_5__* virt; } ;
struct i2o_controller {int /*<<< orphan*/  name; int /*<<< orphan*/  promise; int /*<<< orphan*/  no_quiesce; TYPE_4__ status; TYPE_1__ status_block; } ;
struct TYPE_12__ {int /*<<< orphan*/  iop_state; } ;
typedef  TYPE_5__ i2o_status_block ;
struct TYPE_13__ {int context; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAPTER_STATE_RESET ; 
 int ADAPTER_TID ; 
 int EIGHT_WORD_MSG_SIZE ; 
 int EPERM ; 
 int ETIMEDOUT ; 
 int HOST_TID ; 
 unsigned long HZ ; 
 int I2O_CMD_ADAPTER_RESET ; 
#define  I2O_CMD_IN_PROGRESS 129 
#define  I2O_CMD_REJECTED 128 
 unsigned long I2O_TIMEOUT_MESSAGE_GET ; 
 unsigned long I2O_TIMEOUT_RESET ; 
 scalar_t__ IS_ERR (struct i2o_message*) ; 
 int PTR_ERR (struct i2o_message*) ; 
 int SGL_OFFSET_0 ; 
 void* cpu_to_le32 (int) ; 
 int i2o_dma_high (int /*<<< orphan*/ ) ; 
 int i2o_dma_low (int /*<<< orphan*/ ) ; 
 TYPE_7__ i2o_exec_driver ; 
 int /*<<< orphan*/  i2o_iop_enable_all () ; 
 int /*<<< orphan*/  i2o_iop_quiesce_all () ; 
 struct i2o_message* i2o_msg_get_wait (struct i2o_controller*,unsigned long) ; 
 int /*<<< orphan*/  i2o_msg_nop (struct i2o_controller*,struct i2o_message*) ; 
 int /*<<< orphan*/  i2o_msg_post (struct i2o_controller*,struct i2o_message*) ; 
 int /*<<< orphan*/  i2o_status_get (struct i2o_controller*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  osm_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osm_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osm_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int i2o_iop_reset(struct i2o_controller *c)
{
	volatile u8 *status = c->status.virt;
	struct i2o_message *msg;
	unsigned long timeout;
	i2o_status_block *sb = c->status_block.virt;
	int rc = 0;

	osm_debug("%s: Resetting controller\n", c->name);

	msg = i2o_msg_get_wait(c, I2O_TIMEOUT_MESSAGE_GET);
	if (IS_ERR(msg))
		return PTR_ERR(msg);

	memset(c->status_block.virt, 0, 8);

	/* Quiesce all IOPs first */
	i2o_iop_quiesce_all();

	msg->u.head[0] = cpu_to_le32(EIGHT_WORD_MSG_SIZE | SGL_OFFSET_0);
	msg->u.head[1] =
	    cpu_to_le32(I2O_CMD_ADAPTER_RESET << 24 | HOST_TID << 12 |
			ADAPTER_TID);
	msg->u.s.icntxt = cpu_to_le32(i2o_exec_driver.context);
	msg->u.s.tcntxt = cpu_to_le32(0x00000000);
	msg->body[0] = cpu_to_le32(0x00000000);
	msg->body[1] = cpu_to_le32(0x00000000);
	msg->body[2] = cpu_to_le32(i2o_dma_low(c->status.phys));
	msg->body[3] = cpu_to_le32(i2o_dma_high(c->status.phys));

	i2o_msg_post(c, msg);

	/* Wait for a reply */
	timeout = jiffies + I2O_TIMEOUT_RESET * HZ;
	while (!*status) {
		if (time_after(jiffies, timeout))
			break;

		schedule_timeout_uninterruptible(1);
	}

	switch (*status) {
	case I2O_CMD_REJECTED:
		osm_warn("%s: IOP reset rejected\n", c->name);
		rc = -EPERM;
		break;

	case I2O_CMD_IN_PROGRESS:
		/*
		 * Once the reset is sent, the IOP goes into the INIT state
		 * which is indeterminate. We need to wait until the IOP has
		 * rebooted before we can let the system talk to it. We read
		 * the inbound Free_List until a message is available. If we
		 * can't read one in the given ammount of time, we assume the
		 * IOP could not reboot properly.
		 */
		osm_debug("%s: Reset in progress, waiting for reboot...\n",
			  c->name);

		while (IS_ERR(msg = i2o_msg_get_wait(c, I2O_TIMEOUT_RESET))) {
			if (time_after(jiffies, timeout)) {
				osm_err("%s: IOP reset timeout.\n", c->name);
				rc = PTR_ERR(msg);
				goto exit;
			}
			schedule_timeout_uninterruptible(1);
		}
		i2o_msg_nop(c, msg);

		/* from here all quiesce commands are safe */
		c->no_quiesce = 0;

		/* verify if controller is in state RESET */
		i2o_status_get(c);

		if (!c->promise && (sb->iop_state != ADAPTER_STATE_RESET))
			osm_warn("%s: reset completed, but adapter not in RESET"
				 " state.\n", c->name);
		else
			osm_debug("%s: reset completed.\n", c->name);

		break;

	default:
		osm_err("%s: IOP reset timeout.\n", c->name);
		rc = -ETIMEDOUT;
		break;
	}

      exit:
	/* Enable all IOPs */
	i2o_iop_enable_all();

	return rc;
}