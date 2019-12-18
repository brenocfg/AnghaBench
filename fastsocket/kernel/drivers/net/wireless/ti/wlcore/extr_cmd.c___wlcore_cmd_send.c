#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct wl1271_cmd_header {scalar_t__ status; int /*<<< orphan*/  id; } ;
struct wl1271 {scalar_t__ state; int /*<<< orphan*/  cmd_box_addr; TYPE_1__* ops; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int (* trigger_cmd ) (struct wl1271*,int /*<<< orphan*/ ,void*,size_t) ;} ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  REG_INTERRUPT_ACK ; 
 int /*<<< orphan*/  REG_INTERRUPT_NO_CLEAR ; 
 scalar_t__ WARN_ON (int) ; 
 int WL1271_ACX_INTR_CMD_COMPLETE ; 
 scalar_t__ WL1271_CMD_FAST_POLL_COUNT ; 
 int /*<<< orphan*/  WL1271_COMMAND_TIMEOUT ; 
 int /*<<< orphan*/  WL1271_FLAG_IN_ELP ; 
 scalar_t__ WLCORE_STATE_RESTARTING ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 unsigned long jiffies ; 
 scalar_t__ le16_to_cpu (scalar_t__) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int stub1 (struct wl1271*,int /*<<< orphan*/ ,void*,size_t) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int unlikely (int) ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 
 int wlcore_read (struct wl1271*,int /*<<< orphan*/ ,struct wl1271_cmd_header*,size_t,int) ; 
 int wlcore_read_reg (struct wl1271*,int /*<<< orphan*/ ,int*) ; 
 int wlcore_write (struct wl1271*,int /*<<< orphan*/ ,void*,size_t,int) ; 
 int wlcore_write_reg (struct wl1271*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __wlcore_cmd_send(struct wl1271 *wl, u16 id, void *buf,
			     size_t len, size_t res_len)
{
	struct wl1271_cmd_header *cmd;
	unsigned long timeout;
	u32 intr;
	int ret;
	u16 status;
	u16 poll_count = 0;

	if (WARN_ON(unlikely(wl->state == WLCORE_STATE_RESTARTING)))
		return -EIO;

	cmd = buf;
	cmd->id = cpu_to_le16(id);
	cmd->status = 0;

	WARN_ON(len % 4 != 0);
	WARN_ON(test_bit(WL1271_FLAG_IN_ELP, &wl->flags));

	ret = wlcore_write(wl, wl->cmd_box_addr, buf, len, false);
	if (ret < 0)
		return ret;

	/*
	 * TODO: we just need this because one bit is in a different
	 * place.  Is there any better way?
	 */
	ret = wl->ops->trigger_cmd(wl, wl->cmd_box_addr, buf, len);
	if (ret < 0)
		return ret;

	timeout = jiffies + msecs_to_jiffies(WL1271_COMMAND_TIMEOUT);

	ret = wlcore_read_reg(wl, REG_INTERRUPT_NO_CLEAR, &intr);
	if (ret < 0)
		return ret;

	while (!(intr & WL1271_ACX_INTR_CMD_COMPLETE)) {
		if (time_after(jiffies, timeout)) {
			wl1271_error("command complete timeout");
			return -ETIMEDOUT;
		}

		poll_count++;
		if (poll_count < WL1271_CMD_FAST_POLL_COUNT)
			udelay(10);
		else
			msleep(1);

		ret = wlcore_read_reg(wl, REG_INTERRUPT_NO_CLEAR, &intr);
		if (ret < 0)
			return ret;
	}

	/* read back the status code of the command */
	if (res_len == 0)
		res_len = sizeof(struct wl1271_cmd_header);

	ret = wlcore_read(wl, wl->cmd_box_addr, cmd, res_len, false);
	if (ret < 0)
		return ret;

	status = le16_to_cpu(cmd->status);

	ret = wlcore_write_reg(wl, REG_INTERRUPT_ACK,
			       WL1271_ACX_INTR_CMD_COMPLETE);
	if (ret < 0)
		return ret;

	return status;
}