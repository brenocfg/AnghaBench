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
struct adapter {int flags; int /*<<< orphan*/  work_lock; int /*<<< orphan*/  fatal_error_handler_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_XGM_RX_CTRL ; 
 int /*<<< orphan*/  A_XGM_TX_CTRL ; 
 int /*<<< orphan*/  CH_ALERT (struct adapter*,char*,...) ; 
 int FULL_INIT_DONE ; 
 int /*<<< orphan*/  XGM_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cxgb3_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t3_cim_ctl_blk_read (struct adapter*,int,int,unsigned int*) ; 
 int /*<<< orphan*/  t3_intr_disable (struct adapter*) ; 
 int /*<<< orphan*/  t3_sge_stop (struct adapter*) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void t3_fatal_err(struct adapter *adapter)
{
	unsigned int fw_status[4];

	if (adapter->flags & FULL_INIT_DONE) {
		t3_sge_stop(adapter);
		t3_write_reg(adapter, A_XGM_TX_CTRL, 0);
		t3_write_reg(adapter, A_XGM_RX_CTRL, 0);
		t3_write_reg(adapter, XGM_REG(A_XGM_TX_CTRL, 1), 0);
		t3_write_reg(adapter, XGM_REG(A_XGM_RX_CTRL, 1), 0);

		spin_lock(&adapter->work_lock);
		t3_intr_disable(adapter);
		queue_work(cxgb3_wq, &adapter->fatal_error_handler_task);
		spin_unlock(&adapter->work_lock);
	}
	CH_ALERT(adapter, "encountered fatal error, operation suspended\n");
	if (!t3_cim_ctl_blk_read(adapter, 0xa0, 4, fw_status))
		CH_ALERT(adapter, "FW status: 0x%x, 0x%x, 0x%x, 0x%x\n",
			 fw_status[0], fw_status[1],
			 fw_status[2], fw_status[3]);
}