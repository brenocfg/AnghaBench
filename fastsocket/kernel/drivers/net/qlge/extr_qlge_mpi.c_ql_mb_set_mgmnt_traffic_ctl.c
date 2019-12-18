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
typedef  int /*<<< orphan*/  u32 ;
struct ql_adapter {int /*<<< orphan*/  ndev; } ;
struct mbox_params {int in_count; int out_count; scalar_t__* mbox_out; int /*<<< orphan*/ * mbox_in; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  MB_CMD_SET_MGMNT_TFK_CTL ; 
 scalar_t__ MB_CMD_STS_ERR ; 
 scalar_t__ MB_CMD_STS_GOOD ; 
 scalar_t__ MB_CMD_STS_INVLD_CMD ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  memset (struct mbox_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_printk (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int ql_mailbox_command (struct ql_adapter*,struct mbox_params*) ; 

int ql_mb_set_mgmnt_traffic_ctl(struct ql_adapter *qdev, u32 control)
{
	struct mbox_params mbc;
	struct mbox_params *mbcp = &mbc;
	int status;

	memset(mbcp, 0, sizeof(struct mbox_params));

	mbcp->in_count = 1;
	mbcp->out_count = 2;

	mbcp->mbox_in[0] = MB_CMD_SET_MGMNT_TFK_CTL;
	mbcp->mbox_in[1] = control;

	status = ql_mailbox_command(qdev, mbcp);
	if (status)
		return status;

	if (mbcp->mbox_out[0] == MB_CMD_STS_GOOD)
		return status;

	if (mbcp->mbox_out[0] == MB_CMD_STS_INVLD_CMD) {
		 netif_printk(qdev, drv, KERN_DEBUG, qdev->ndev,
			  "Command not supported by firmware version.\n");
		status = -EINVAL;
	} else if (mbcp->mbox_out[0] == MB_CMD_STS_ERR) {
		/* This indicates that the firmware is
		 * already in the state we are trying to
		 * change it to.
		 */
		netif_err(qdev, drv, qdev->ndev,
			  "Command parameters make no change.\n");
	}
	return status;
}