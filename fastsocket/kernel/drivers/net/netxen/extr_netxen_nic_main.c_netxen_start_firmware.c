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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ port_type; int /*<<< orphan*/  revision_id; } ;
struct netxen_adapter {scalar_t__ need_fw_reset; TYPE_1__ ahw; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRB_CMDPEG_STATE ; 
 int /*<<< orphan*/  CRB_DMA_SHIFT ; 
 int /*<<< orphan*/  CRB_DRIVER_VERSION ; 
 int EIO ; 
 int /*<<< orphan*/  NETXEN_CAM_RAM (int) ; 
 int /*<<< orphan*/  NETXEN_MAC_ADDR_CNTL_REG ; 
 int /*<<< orphan*/  NETXEN_NIC_PEG_TUNE ; 
 scalar_t__ NETXEN_NIC_XGBE ; 
 int /*<<< orphan*/  NETXEN_PEG_HALT_STATUS1 ; 
 int /*<<< orphan*/  NETXEN_PEG_HALT_STATUS2 ; 
 int NXRD32 (struct netxen_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NXWR32 (struct netxen_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NX_CRB_DEV_STATE ; 
 int NX_DEV_FAILED ; 
 int NX_DEV_READY ; 
 scalar_t__ NX_IS_REVISION_P2 (int /*<<< orphan*/ ) ; 
 scalar_t__ NX_IS_REVISION_P3 (int /*<<< orphan*/ ) ; 
 int _NETXEN_NIC_LINUX_MAJOR ; 
 int _NETXEN_NIC_LINUX_MINOR ; 
 int _NETXEN_NIC_LINUX_SUBVERSION ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ netxen_api_lock (struct netxen_adapter*) ; 
 int /*<<< orphan*/  netxen_api_unlock (struct netxen_adapter*) ; 
 int netxen_can_start_firmware (struct netxen_adapter*) ; 
 int netxen_check_hw_init (struct netxen_adapter*,int) ; 
 int /*<<< orphan*/  netxen_check_options (struct netxen_adapter*) ; 
 int /*<<< orphan*/  netxen_free_dummy_dma (struct netxen_adapter*) ; 
 int netxen_init_dummy_dma (struct netxen_adapter*) ; 
 int netxen_load_firmware (struct netxen_adapter*) ; 
 int netxen_need_fw_reset (struct netxen_adapter*) ; 
 int /*<<< orphan*/  netxen_pcie_strap_init (struct netxen_adapter*) ; 
 int netxen_phantom_init (struct netxen_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netxen_pinit_from_rom (struct netxen_adapter*) ; 
 int /*<<< orphan*/  netxen_release_firmware (struct netxen_adapter*) ; 
 int /*<<< orphan*/  netxen_request_firmware (struct netxen_adapter*) ; 
 int /*<<< orphan*/  netxen_set_port_mode (struct netxen_adapter*) ; 
 int nx_set_dma_mask (struct netxen_adapter*) ; 
 int /*<<< orphan*/  nx_update_dma_mask (struct netxen_adapter*) ; 

__attribute__((used)) static int
netxen_start_firmware(struct netxen_adapter *adapter)
{
	int val, err, first_boot, state;
	struct pci_dev *pdev = adapter->pdev;

	/* required for NX2031 dummy dma */
	err = nx_set_dma_mask(adapter);
	if (err)
		return err;

	err = netxen_can_start_firmware(adapter);

	if (err < 0)
		return err;

	if (!err)
		goto wait_init;

	first_boot = NXRD32(adapter, NETXEN_CAM_RAM(0x1fc));

	err = netxen_check_hw_init(adapter, first_boot);
	if (err) {
		dev_err(&pdev->dev, "error in init HW init sequence\n");
		return err;
	}

	netxen_request_firmware(adapter);

	err = netxen_need_fw_reset(adapter);
	if (err < 0)
		goto err_out;
	if (err == 0)
		goto pcie_strap_init;

	if (first_boot != 0x55555555) {
		NXWR32(adapter, CRB_CMDPEG_STATE, 0);
		netxen_pinit_from_rom(adapter);
		msleep(1);
	}

	NXWR32(adapter, CRB_DMA_SHIFT, 0x55555555);
	NXWR32(adapter, NETXEN_PEG_HALT_STATUS1, 0);
	NXWR32(adapter, NETXEN_PEG_HALT_STATUS2, 0);

	if (NX_IS_REVISION_P3(adapter->ahw.revision_id))
		netxen_set_port_mode(adapter);

	err = netxen_load_firmware(adapter);
	if (err)
		goto err_out;

	netxen_release_firmware(adapter);

	if (NX_IS_REVISION_P2(adapter->ahw.revision_id)) {

		/* Initialize multicast addr pool owners */
		val = 0x7654;
		if (adapter->ahw.port_type == NETXEN_NIC_XGBE)
			val |= 0x0f000000;
		NXWR32(adapter, NETXEN_MAC_ADDR_CNTL_REG, val);

	}

	err = netxen_init_dummy_dma(adapter);
	if (err)
		goto err_out;

	/*
	 * Tell the hardware our version number.
	 */
	val = (_NETXEN_NIC_LINUX_MAJOR << 16)
		| ((_NETXEN_NIC_LINUX_MINOR << 8))
		| (_NETXEN_NIC_LINUX_SUBVERSION);
	NXWR32(adapter, CRB_DRIVER_VERSION, val);

pcie_strap_init:
	if (NX_IS_REVISION_P3(adapter->ahw.revision_id))
		netxen_pcie_strap_init(adapter);

wait_init:
	/* Handshake with the card before we register the devices. */
	err = netxen_phantom_init(adapter, NETXEN_NIC_PEG_TUNE);
	if (err) {
		netxen_free_dummy_dma(adapter);
		goto err_out;
	}

	if (netxen_api_lock(adapter))
		return -EIO;
	state = NXRD32(adapter, NX_CRB_DEV_STATE);

	if (state == NX_DEV_FAILED)
		return 1;

	NXWR32(adapter, NX_CRB_DEV_STATE, NX_DEV_READY);
	netxen_api_unlock(adapter);

	nx_update_dma_mask(adapter);

	netxen_check_options(adapter);

	adapter->need_fw_reset = 0;

	/* fall through and release firmware */

err_out:
	netxen_release_firmware(adapter);
	return err;
}