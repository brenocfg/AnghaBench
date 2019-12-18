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
typedef  int u8 ;
struct pci_dev {scalar_t__ device; } ;
struct net_device {int dummy; } ;
struct cnic_local {int /*<<< orphan*/  close_conn; int /*<<< orphan*/  disable_int_sync; int /*<<< orphan*/  enable_int; int /*<<< orphan*/  stop_cm; int /*<<< orphan*/  start_cm; int /*<<< orphan*/  free_resc; int /*<<< orphan*/  alloc_resc; int /*<<< orphan*/  setup_pgtbl; int /*<<< orphan*/  stop_hw; int /*<<< orphan*/  start_hw; int /*<<< orphan*/ * cnic_ops; int /*<<< orphan*/  chip_id; struct cnic_eth_dev* ethdev; } ;
struct cnic_eth_dev {int /*<<< orphan*/  max_iscsi_conn; int /*<<< orphan*/  chip_id; struct pci_dev* pdev; } ;
struct cnic_dev {int /*<<< orphan*/  max_iscsi_conn; struct pci_dev* pcidev; struct cnic_local* cnic_priv; int /*<<< orphan*/  submit_kwqes; int /*<<< orphan*/  flags; } ;
struct bnx2 {struct cnic_eth_dev* (* cnic_probe ) (struct net_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CNIC_F_BNX2_CLASS ; 
 scalar_t__ PCI_DEVICE_ID_NX2_5709 ; 
 scalar_t__ PCI_DEVICE_ID_NX2_5709S ; 
 int /*<<< orphan*/  PCI_REVISION_ID ; 
 int /*<<< orphan*/  cnic_alloc_bnx2_resc ; 
 struct cnic_dev* cnic_alloc_dev (struct net_device*,struct pci_dev*) ; 
 int /*<<< orphan*/  cnic_bnx2_ops ; 
 int /*<<< orphan*/  cnic_close_bnx2_conn ; 
 int /*<<< orphan*/  cnic_cm_init_bnx2_hw ; 
 int /*<<< orphan*/  cnic_cm_stop_bnx2_hw ; 
 int /*<<< orphan*/  cnic_disable_bnx2_int_sync ; 
 int /*<<< orphan*/  cnic_enable_bnx2_int ; 
 int /*<<< orphan*/  cnic_free_resc ; 
 int /*<<< orphan*/  cnic_setup_page_tbl ; 
 int /*<<< orphan*/  cnic_start_bnx2_hw ; 
 int /*<<< orphan*/  cnic_stop_bnx2_hw ; 
 int /*<<< orphan*/  cnic_submit_bnx2_kwqes ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 struct bnx2* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_dev_get (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct cnic_eth_dev* stub1 (struct net_device*) ; 

__attribute__((used)) static struct cnic_dev *init_bnx2_cnic(struct net_device *dev)
{
	struct pci_dev *pdev;
	struct cnic_dev *cdev;
	struct cnic_local *cp;
	struct bnx2 *bp = netdev_priv(dev);
	struct cnic_eth_dev *ethdev = NULL;

	if (bp->cnic_probe)
		ethdev = (bp->cnic_probe)(dev);

	if (!ethdev)
		return NULL;

	pdev = ethdev->pdev;
	if (!pdev)
		return NULL;

	dev_hold(dev);
	pci_dev_get(pdev);
	if (pdev->device == PCI_DEVICE_ID_NX2_5709 ||
	    pdev->device == PCI_DEVICE_ID_NX2_5709S) {
		u8 rev;

		pci_read_config_byte(pdev, PCI_REVISION_ID, &rev);
		if (rev < 0x10) {
			pci_dev_put(pdev);
			goto cnic_err;
		}
	}
	pci_dev_put(pdev);

	cdev = cnic_alloc_dev(dev, pdev);
	if (cdev == NULL)
		goto cnic_err;

	set_bit(CNIC_F_BNX2_CLASS, &cdev->flags);
	cdev->submit_kwqes = cnic_submit_bnx2_kwqes;

	cp = cdev->cnic_priv;
	cp->ethdev = ethdev;
	cdev->pcidev = pdev;
	cp->chip_id = ethdev->chip_id;

	cdev->max_iscsi_conn = ethdev->max_iscsi_conn;

	cp->cnic_ops = &cnic_bnx2_ops;
	cp->start_hw = cnic_start_bnx2_hw;
	cp->stop_hw = cnic_stop_bnx2_hw;
	cp->setup_pgtbl = cnic_setup_page_tbl;
	cp->alloc_resc = cnic_alloc_bnx2_resc;
	cp->free_resc = cnic_free_resc;
	cp->start_cm = cnic_cm_init_bnx2_hw;
	cp->stop_cm = cnic_cm_stop_bnx2_hw;
	cp->enable_int = cnic_enable_bnx2_int;
	cp->disable_int_sync = cnic_disable_bnx2_int_sync;
	cp->close_conn = cnic_close_bnx2_conn;
	return cdev;

cnic_err:
	dev_put(dev);
	return NULL;
}