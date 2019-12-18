#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct wl1251_cmd_header {scalar_t__ status; int /*<<< orphan*/  id; } ;
struct wl1251 {int /*<<< orphan*/  cmd_box_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_REG_INTERRUPT_ACK ; 
 int /*<<< orphan*/  ACX_REG_INTERRUPT_NO_CLEAR ; 
 int /*<<< orphan*/  ACX_REG_INTERRUPT_TRIG ; 
 int ETIMEDOUT ; 
 int INTR_TRIG_CMD ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int WL1251_ACX_INTR_CMD_COMPLETE ; 
 int /*<<< orphan*/  WL1251_COMMAND_TIMEOUT ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  wl1251_error (char*) ; 
 int /*<<< orphan*/  wl1251_mem_write (struct wl1251*,int /*<<< orphan*/ ,void*,size_t) ; 
 int wl1251_reg_read32 (struct wl1251*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1251_reg_write32 (struct wl1251*,int /*<<< orphan*/ ,int) ; 

int wl1251_cmd_send(struct wl1251 *wl, u16 id, void *buf, size_t len)
{
	struct wl1251_cmd_header *cmd;
	unsigned long timeout;
	u32 intr;
	int ret = 0;

	cmd = buf;
	cmd->id = id;
	cmd->status = 0;

	WARN_ON(len % 4 != 0);

	wl1251_mem_write(wl, wl->cmd_box_addr, buf, len);

	wl1251_reg_write32(wl, ACX_REG_INTERRUPT_TRIG, INTR_TRIG_CMD);

	timeout = jiffies + msecs_to_jiffies(WL1251_COMMAND_TIMEOUT);

	intr = wl1251_reg_read32(wl, ACX_REG_INTERRUPT_NO_CLEAR);
	while (!(intr & WL1251_ACX_INTR_CMD_COMPLETE)) {
		if (time_after(jiffies, timeout)) {
			wl1251_error("command complete timeout");
			ret = -ETIMEDOUT;
			goto out;
		}

		msleep(1);

		intr = wl1251_reg_read32(wl, ACX_REG_INTERRUPT_NO_CLEAR);
	}

	wl1251_reg_write32(wl, ACX_REG_INTERRUPT_ACK,
			   WL1251_ACX_INTR_CMD_COMPLETE);

out:
	return ret;
}