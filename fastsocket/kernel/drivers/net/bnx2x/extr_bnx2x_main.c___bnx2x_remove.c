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
struct pci_dev {int /*<<< orphan*/  enable_cnt; } ;
struct net_device {int dummy; } ;
struct bnx2x {int flags; scalar_t__ doorbells; scalar_t__ regview; int /*<<< orphan*/  wol; int /*<<< orphan*/  sp_rtnl_task; int /*<<< orphan*/  fip_mac; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BC_SUPPORTS_RMMOD_CMD ; 
 int /*<<< orphan*/  BP_NOMCP (struct bnx2x*) ; 
 int /*<<< orphan*/  DRV_MSG_CODE_RMMOD ; 
 scalar_t__ IS_PF (struct bnx2x*) ; 
 scalar_t__ IS_VF (struct bnx2x*) ; 
 int /*<<< orphan*/  NETDEV_HW_ADDR_T_SAN ; 
 int /*<<< orphan*/  NO_FCOE (struct bnx2x*) ; 
 int /*<<< orphan*/  PCI_D0 ; 
 int /*<<< orphan*/  PCI_D3hot ; 
 scalar_t__ SYSTEM_POWER_OFF ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnx2x_dcbnl_update_applist (struct bnx2x*,int) ; 
 int /*<<< orphan*/  bnx2x_disable_msi (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_free_mem_bp (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_fw_command (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_iov_remove_one (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_release_firmware (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_set_power_state (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_vfpf_release (struct bnx2x*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_addr_del (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_close (struct net_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_wake_from_d3 (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 scalar_t__ system_state ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void __bnx2x_remove(struct pci_dev *pdev,
			   struct net_device *dev,
			   struct bnx2x *bp,
			   bool remove_netdev)
{
	/* Delete storage MAC address */
	if (!NO_FCOE(bp)) {
		rtnl_lock();
		dev_addr_del(bp->dev, bp->fip_mac, NETDEV_HW_ADDR_T_SAN);
		rtnl_unlock();
	}

#ifdef BCM_DCBNL
	/* Delete app tlvs from dcbnl */
	bnx2x_dcbnl_update_applist(bp, true);
#endif

	if (IS_PF(bp) &&
	    !BP_NOMCP(bp) &&
	    (bp->flags & BC_SUPPORTS_RMMOD_CMD))
		bnx2x_fw_command(bp, DRV_MSG_CODE_RMMOD, 0);

	/* Close the interface - either directly or implicitly */
	if (remove_netdev) {
		unregister_netdev(dev);
	} else {
		rtnl_lock();
		dev_close(dev);
		rtnl_unlock();
	}

	bnx2x_iov_remove_one(bp);

	/* Power on: we can't let PCI layer write to us while we are in D3 */
	if (IS_PF(bp))
		bnx2x_set_power_state(bp, PCI_D0);

	/* Disable MSI/MSI-X */
	bnx2x_disable_msi(bp);

	/* Power off */
	if (IS_PF(bp))
		bnx2x_set_power_state(bp, PCI_D3hot);

	/* Make sure RESET task is not scheduled before continuing */
	cancel_delayed_work_sync(&bp->sp_rtnl_task);

	/* send message via vfpf channel to release the resources of this vf */
	if (IS_VF(bp))
		bnx2x_vfpf_release(bp);

	/* Assumes no further PCIe PM changes will occur */
	if (system_state == SYSTEM_POWER_OFF) {
		pci_wake_from_d3(pdev, bp->wol);
		pci_set_power_state(pdev, PCI_D3hot);
	}

	if (bp->regview)
		iounmap(bp->regview);

	/* for vf doorbells are part of the regview and were unmapped along with
	 * it. FW is only loaded by PF.
	 */
	if (IS_PF(bp)) {
		if (bp->doorbells)
			iounmap(bp->doorbells);

		bnx2x_release_firmware(bp);
	}
	bnx2x_free_mem_bp(bp);

	if (remove_netdev)
		free_netdev(dev);

	if (atomic_read(&pdev->enable_cnt) == 1)
		pci_release_regions(pdev);

	pci_disable_device(pdev);
	pci_set_drvdata(pdev, NULL);
}