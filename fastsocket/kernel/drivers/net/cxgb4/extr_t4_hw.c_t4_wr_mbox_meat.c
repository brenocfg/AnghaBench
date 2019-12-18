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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct adapter {int /*<<< orphan*/  pdev_dev; TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_2__ {scalar_t__ error_state; } ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
 int /*<<< orphan*/  CIM_PF_MAILBOX_CTRL ; 
 int /*<<< orphan*/  CIM_PF_MAILBOX_DATA ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int FW_CMD_MAX_TIMEOUT ; 
 scalar_t__ FW_CMD_OP_GET (int) ; 
 int FW_CMD_RETVAL (int) ; 
 int FW_CMD_RETVAL_GET (int) ; 
 scalar_t__ FW_DEBUG_CMD ; 
 int MBMSGVALID ; 
 int MBOWNER (int /*<<< orphan*/ ) ; 
 int MBOWNER_GET (int) ; 
 int MBOX_LEN ; 
 int MBOX_OWNER_DRV ; 
 int /*<<< orphan*/  MBOX_OWNER_FW ; 
 int MBOX_OWNER_NONE ; 
 int PF_REG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  dump_mbox (struct adapter*,int,int) ; 
 int /*<<< orphan*/  fw_asrt (struct adapter*,int) ; 
 int /*<<< orphan*/  get_mbox_rpl (struct adapter*,void*,int,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ pci_channel_io_normal ; 
 int t4_read_reg (struct adapter*,int) ; 
 int t4_read_reg64 (struct adapter*,int) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int,int) ; 
 int /*<<< orphan*/  t4_write_reg64 (struct adapter*,int,int /*<<< orphan*/ ) ; 

int t4_wr_mbox_meat(struct adapter *adap, int mbox, const void *cmd, int size,
		    void *rpl, bool sleep_ok)
{
	static const int delay[] = {
		1, 1, 3, 5, 10, 10, 20, 50, 100, 200
	};

	u32 v;
	u64 res;
	int i, ms, delay_idx;
	const __be64 *p = cmd;
	u32 data_reg = PF_REG(mbox, CIM_PF_MAILBOX_DATA);
	u32 ctl_reg = PF_REG(mbox, CIM_PF_MAILBOX_CTRL);

	if ((size & 15) || size > MBOX_LEN)
		return -EINVAL;

	/*
	 * If the device is off-line, as in EEH, commands will time out.
	 * Fail them early so we don't waste time waiting.
	 */
	if (adap->pdev->error_state != pci_channel_io_normal)
		return -EIO;

	v = MBOWNER_GET(t4_read_reg(adap, ctl_reg));
	for (i = 0; v == MBOX_OWNER_NONE && i < 3; i++)
		v = MBOWNER_GET(t4_read_reg(adap, ctl_reg));

	if (v != MBOX_OWNER_DRV)
		return v ? -EBUSY : -ETIMEDOUT;

	for (i = 0; i < size; i += 8)
		t4_write_reg64(adap, data_reg + i, be64_to_cpu(*p++));

	t4_write_reg(adap, ctl_reg, MBMSGVALID | MBOWNER(MBOX_OWNER_FW));
	t4_read_reg(adap, ctl_reg);          /* flush write */

	delay_idx = 0;
	ms = delay[0];

	for (i = 0; i < FW_CMD_MAX_TIMEOUT; i += ms) {
		if (sleep_ok) {
			ms = delay[delay_idx];  /* last element may repeat */
			if (delay_idx < ARRAY_SIZE(delay) - 1)
				delay_idx++;
			msleep(ms);
		} else
			mdelay(ms);

		v = t4_read_reg(adap, ctl_reg);
		if (MBOWNER_GET(v) == MBOX_OWNER_DRV) {
			if (!(v & MBMSGVALID)) {
				t4_write_reg(adap, ctl_reg, 0);
				continue;
			}

			res = t4_read_reg64(adap, data_reg);
			if (FW_CMD_OP_GET(res >> 32) == FW_DEBUG_CMD) {
				fw_asrt(adap, data_reg);
				res = FW_CMD_RETVAL(EIO);
			} else if (rpl)
				get_mbox_rpl(adap, rpl, size / 8, data_reg);

			if (FW_CMD_RETVAL_GET((int)res))
				dump_mbox(adap, mbox, data_reg);
			t4_write_reg(adap, ctl_reg, 0);
			return -FW_CMD_RETVAL_GET((int)res);
		}
	}

	dump_mbox(adap, mbox, data_reg);
	dev_err(adap->pdev_dev, "command %#x in mailbox %d timed out\n",
		*(const u8 *)cmd, mbox);
	return -ETIMEDOUT;
}