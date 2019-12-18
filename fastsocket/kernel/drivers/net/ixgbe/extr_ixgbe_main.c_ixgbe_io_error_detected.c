#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct pci_dev {int devfn; TYPE_1__* bus; } ;
struct net_device {int dummy; } ;
struct TYPE_5__ {int type; } ;
struct TYPE_6__ {TYPE_2__ mac; } ;
struct ixgbe_adapter {scalar_t__ num_vfs; int /*<<< orphan*/  vferr_refcount; TYPE_3__ hw; struct net_device* netdev; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;
typedef  scalar_t__ pci_channel_state_t ;
struct TYPE_4__ {struct pci_dev* self; } ;

/* Variables and functions */
 unsigned int IXGBE_82599_VF_DEVICE_ID ; 
 unsigned int IXGBE_X540_VF_DEVICE_ID ; 
 scalar_t__ PCI_ERR_HEADER_LOG ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_NEED_RESET ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_RECOVERED ; 
 scalar_t__ PCI_EXP_TYPE_ROOT_PORT ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_ERR ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_INTEL ; 
 int /*<<< orphan*/  e_dev_err (char*,int,...) ; 
 int /*<<< orphan*/  ixgbe_down (struct ixgbe_adapter*) ; 
 int ixgbe_mac_82598EB ; 
#define  ixgbe_mac_82599EB 129 
#define  ixgbe_mac_X540 128 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 scalar_t__ pci_channel_io_perm_failure ; 
 int /*<<< orphan*/  pci_cleanup_aer_uncorrect_error_status (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,unsigned int,struct pci_dev*) ; 
 struct ixgbe_adapter* pci_get_drvdata (struct pci_dev*) ; 
 scalar_t__ pci_pcie_type (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int,int) ; 

__attribute__((used)) static pci_ers_result_t ixgbe_io_error_detected(struct pci_dev *pdev,
						pci_channel_state_t state)
{
	struct ixgbe_adapter *adapter = pci_get_drvdata(pdev);
	struct net_device *netdev = adapter->netdev;

#ifdef CONFIG_PCI_IOV
	struct pci_dev *bdev, *vfdev;
	u32 dw0, dw1, dw2, dw3;
	int vf, pos;
	u16 req_id, pf_func;

	if (adapter->hw.mac.type == ixgbe_mac_82598EB ||
	    adapter->num_vfs == 0)
		goto skip_bad_vf_detection;

	bdev = pdev->bus->self;
	while (bdev && (pci_pcie_type(bdev) != PCI_EXP_TYPE_ROOT_PORT))
		bdev = bdev->bus->self;

	if (!bdev)
		goto skip_bad_vf_detection;

	pos = pci_find_ext_capability(bdev, PCI_EXT_CAP_ID_ERR);
	if (!pos)
		goto skip_bad_vf_detection;

	pci_read_config_dword(bdev, pos + PCI_ERR_HEADER_LOG, &dw0);
	pci_read_config_dword(bdev, pos + PCI_ERR_HEADER_LOG + 4, &dw1);
	pci_read_config_dword(bdev, pos + PCI_ERR_HEADER_LOG + 8, &dw2);
	pci_read_config_dword(bdev, pos + PCI_ERR_HEADER_LOG + 12, &dw3);

	req_id = dw1 >> 16;
	/* On the 82599 if bit 7 of the requestor ID is set then it's a VF */
	if (!(req_id & 0x0080))
		goto skip_bad_vf_detection;

	pf_func = req_id & 0x01;
	if ((pf_func & 1) == (pdev->devfn & 1)) {
		unsigned int device_id;

		vf = (req_id & 0x7F) >> 1;
		e_dev_err("VF %d has caused a PCIe error\n", vf);
		e_dev_err("TLP: dw0: %8.8x\tdw1: %8.8x\tdw2: "
				"%8.8x\tdw3: %8.8x\n",
		dw0, dw1, dw2, dw3);
		switch (adapter->hw.mac.type) {
		case ixgbe_mac_82599EB:
			device_id = IXGBE_82599_VF_DEVICE_ID;
			break;
		case ixgbe_mac_X540:
			device_id = IXGBE_X540_VF_DEVICE_ID;
			break;
		default:
			device_id = 0;
			break;
		}

		/* Find the pci device of the offending VF */
		vfdev = pci_get_device(PCI_VENDOR_ID_INTEL, device_id, NULL);
		while (vfdev) {
			if (vfdev->devfn == (req_id & 0xFF))
				break;
			vfdev = pci_get_device(PCI_VENDOR_ID_INTEL,
					       device_id, vfdev);
		}
		/*
		 * There's a slim chance the VF could have been hot plugged,
		 * so if it is no longer present we don't need to issue the
		 * VFLR.  Just clean up the AER in that case.
		 */
		if (vfdev) {
			e_dev_err("Issuing VFLR to VF %d\n", vf);
			pci_write_config_dword(vfdev, 0xA8, 0x00008000);
			/* Free device reference count */
			pci_dev_put(vfdev);
		}

		pci_cleanup_aer_uncorrect_error_status(pdev);
	}

	/*
	 * Even though the error may have occurred on the other port
	 * we still need to increment the vf error reference count for
	 * both ports because the I/O resume function will be called
	 * for both of them.
	 */
	adapter->vferr_refcount++;

	return PCI_ERS_RESULT_RECOVERED;

skip_bad_vf_detection:
#endif /* CONFIG_PCI_IOV */
	netif_device_detach(netdev);

	if (state == pci_channel_io_perm_failure)
		return PCI_ERS_RESULT_DISCONNECT;

	if (netif_running(netdev))
		ixgbe_down(adapter);
	pci_disable_device(pdev);

	/* Request a slot reset. */
	return PCI_ERS_RESULT_NEED_RESET;
}