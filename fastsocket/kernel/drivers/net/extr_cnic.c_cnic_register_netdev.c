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
struct cnic_local {int /*<<< orphan*/  cnic_ops; struct cnic_eth_dev* ethdev; } ;
struct cnic_eth_dev {int drv_state; int (* drv_register_cnic ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cnic_dev*) ;int /*<<< orphan*/  max_iscsi_conn; } ;
struct cnic_dev {int /*<<< orphan*/  max_iscsi_conn; int /*<<< orphan*/  netdev; struct cnic_local* cnic_priv; } ;

/* Variables and functions */
 int CNIC_DRV_STATE_NO_ISCSI ; 
 int CNIC_DRV_STATE_REGD ; 
 int ENODEV ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cnic_dev*) ; 

__attribute__((used)) static int cnic_register_netdev(struct cnic_dev *dev)
{
	struct cnic_local *cp = dev->cnic_priv;
	struct cnic_eth_dev *ethdev = cp->ethdev;
	int err;

	if (!ethdev)
		return -ENODEV;

	if (ethdev->drv_state & CNIC_DRV_STATE_REGD)
		return 0;

	err = ethdev->drv_register_cnic(dev->netdev, cp->cnic_ops, dev);
	if (err)
		netdev_err(dev->netdev, "register_cnic failed\n");

	/* Read iSCSI config again.  On some bnx2x device, iSCSI config
	 * can change after firmware is downloaded.
	 */
	dev->max_iscsi_conn = ethdev->max_iscsi_conn;
	if (ethdev->drv_state & CNIC_DRV_STATE_NO_ISCSI)
		dev->max_iscsi_conn = 0;

	return err;
}