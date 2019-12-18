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
struct falcon_nic_data {int /*<<< orphan*/  pci_dev2; } ;
struct efx_nic {int /*<<< orphan*/  pci_dev; int /*<<< orphan*/  net_dev; struct falcon_nic_data* nic_data; } ;
typedef  enum reset_type { ____Placeholder_reset_type } reset_type ;
typedef  int /*<<< orphan*/  efx_oword_t ;

/* Variables and functions */
 scalar_t__ EFX_OWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EFX_POPULATE_OWORD_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EFX_POPULATE_OWORD_7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  FFE_AB_EXT_PHY_RST_DUR_10240US ; 
 int /*<<< orphan*/  FRF_AB_EE_RST_CTL ; 
 int /*<<< orphan*/  FRF_AB_EXT_PHY_RST_CTL ; 
 int /*<<< orphan*/  FRF_AB_EXT_PHY_RST_DUR ; 
 int /*<<< orphan*/  FRF_AB_PCIE_CORE_RST_CTL ; 
 int /*<<< orphan*/  FRF_AB_PCIE_NSTKY_RST_CTL ; 
 int /*<<< orphan*/  FRF_AB_PCIE_SD_RST_CTL ; 
 int /*<<< orphan*/  FRF_AB_SWRST ; 
 int /*<<< orphan*/  FR_AB_GLB_CTL ; 
 int HZ ; 
 int /*<<< orphan*/  RESET_TYPE (int) ; 
 int RESET_TYPE_INVISIBLE ; 
 int RESET_TYPE_WORLD ; 
 int /*<<< orphan*/  drv ; 
 scalar_t__ efx_nic_is_dual_func (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_reado (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_writeo (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  netif_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pci_restore_state (int /*<<< orphan*/ ) ; 
 int pci_save_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 

__attribute__((used)) static int __falcon_reset_hw(struct efx_nic *efx, enum reset_type method)
{
	struct falcon_nic_data *nic_data = efx->nic_data;
	efx_oword_t glb_ctl_reg_ker;
	int rc;

	netif_dbg(efx, hw, efx->net_dev, "performing %s hardware reset\n",
		  RESET_TYPE(method));

	/* Initiate device reset */
	if (method == RESET_TYPE_WORLD) {
		rc = pci_save_state(efx->pci_dev);
		if (rc) {
			netif_err(efx, drv, efx->net_dev,
				  "failed to backup PCI state of primary "
				  "function prior to hardware reset\n");
			goto fail1;
		}
		if (efx_nic_is_dual_func(efx)) {
			rc = pci_save_state(nic_data->pci_dev2);
			if (rc) {
				netif_err(efx, drv, efx->net_dev,
					  "failed to backup PCI state of "
					  "secondary function prior to "
					  "hardware reset\n");
				goto fail2;
			}
		}

		EFX_POPULATE_OWORD_2(glb_ctl_reg_ker,
				     FRF_AB_EXT_PHY_RST_DUR,
				     FFE_AB_EXT_PHY_RST_DUR_10240US,
				     FRF_AB_SWRST, 1);
	} else {
		EFX_POPULATE_OWORD_7(glb_ctl_reg_ker,
				     /* exclude PHY from "invisible" reset */
				     FRF_AB_EXT_PHY_RST_CTL,
				     method == RESET_TYPE_INVISIBLE,
				     /* exclude EEPROM/flash and PCIe */
				     FRF_AB_PCIE_CORE_RST_CTL, 1,
				     FRF_AB_PCIE_NSTKY_RST_CTL, 1,
				     FRF_AB_PCIE_SD_RST_CTL, 1,
				     FRF_AB_EE_RST_CTL, 1,
				     FRF_AB_EXT_PHY_RST_DUR,
				     FFE_AB_EXT_PHY_RST_DUR_10240US,
				     FRF_AB_SWRST, 1);
	}
	efx_writeo(efx, &glb_ctl_reg_ker, FR_AB_GLB_CTL);

	netif_dbg(efx, hw, efx->net_dev, "waiting for hardware reset\n");
	schedule_timeout_uninterruptible(HZ / 20);

	/* Restore PCI configuration if needed */
	if (method == RESET_TYPE_WORLD) {
		if (efx_nic_is_dual_func(efx))
			pci_restore_state(nic_data->pci_dev2);
		pci_restore_state(efx->pci_dev);
		netif_dbg(efx, drv, efx->net_dev,
			  "successfully restored PCI config\n");
	}

	/* Assert that reset complete */
	efx_reado(efx, &glb_ctl_reg_ker, FR_AB_GLB_CTL);
	if (EFX_OWORD_FIELD(glb_ctl_reg_ker, FRF_AB_SWRST) != 0) {
		rc = -ETIMEDOUT;
		netif_err(efx, hw, efx->net_dev,
			  "timed out waiting for hardware reset\n");
		goto fail3;
	}
	netif_dbg(efx, hw, efx->net_dev, "hardware reset complete\n");

	return 0;

	/* pci_save_state() and pci_restore_state() MUST be called in pairs */
fail2:
	pci_restore_state(efx->pci_dev);
fail1:
fail3:
	return rc;
}