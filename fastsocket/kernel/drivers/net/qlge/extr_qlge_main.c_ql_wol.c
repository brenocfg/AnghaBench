#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ql_adapter {int wol; TYPE_1__* ndev; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MB_WOL_DISABLE ; 
 int /*<<< orphan*/  MB_WOL_MAGIC_PKT ; 
 int /*<<< orphan*/  MB_WOL_MODE_ON ; 
 int WAKE_ARP ; 
 int WAKE_BCAST ; 
 int WAKE_MAGIC ; 
 int WAKE_MAGICSECURE ; 
 int WAKE_MCAST ; 
 int WAKE_PHY ; 
 int WAKE_UCAST ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  ifdown ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  netif_info (struct ql_adapter*,int /*<<< orphan*/ ,TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int ql_mb_wol_mode (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int ql_mb_wol_set_magic (struct ql_adapter*,int) ; 

int ql_wol(struct ql_adapter *qdev)
{
	int status = 0;
	u32 wol = MB_WOL_DISABLE;

	/* The CAM is still intact after a reset, but if we
	 * are doing WOL, then we may need to program the
	 * routing regs. We would also need to issue the mailbox
	 * commands to instruct the MPI what to do per the ethtool
	 * settings.
	 */

	if (qdev->wol & (WAKE_ARP | WAKE_MAGICSECURE | WAKE_PHY | WAKE_UCAST |
			WAKE_MCAST | WAKE_BCAST)) {
		netif_err(qdev, ifdown, qdev->ndev,
			  "Unsupported WOL paramter. qdev->wol = 0x%x.\n",
			  qdev->wol);
		return -EINVAL;
	}

	if (qdev->wol & WAKE_MAGIC) {
		status = ql_mb_wol_set_magic(qdev, 1);
		if (status) {
			netif_err(qdev, ifdown, qdev->ndev,
				  "Failed to set magic packet on %s.\n",
				  qdev->ndev->name);
			return status;
		} else
			netif_info(qdev, drv, qdev->ndev,
				   "Enabled magic packet successfully on %s.\n",
				   qdev->ndev->name);

		wol |= MB_WOL_MAGIC_PKT;
	}

	if (qdev->wol) {
		wol |= MB_WOL_MODE_ON;
		status = ql_mb_wol_mode(qdev, wol);
		netif_err(qdev, drv, qdev->ndev,
			  "WOL %s (wol code 0x%x) on %s\n",
			  (status == 0) ? "Sucessfully set" : "Failed",
			  wol, qdev->ndev->name);
	}

	return status;
}