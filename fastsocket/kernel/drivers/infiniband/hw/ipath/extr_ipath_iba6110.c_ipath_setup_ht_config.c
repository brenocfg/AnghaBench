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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ipath_devdata {int ipath_irq; int /*<<< orphan*/  ipath_flags; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  IPATH_SWAP_PIOBUFS ; 
 int /*<<< orphan*/  PCI_CAP_ID_HT ; 
 int __ht_create_irq (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ipath_dev_err (struct ipath_devdata*,char*,...) ; 
 int /*<<< orphan*/  ipath_ht_irq_update ; 
 int pci_find_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_find_next_capability (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  slave_or_pri_blk (struct ipath_devdata*,struct pci_dev*,int,int) ; 

__attribute__((used)) static int ipath_setup_ht_config(struct ipath_devdata *dd,
				 struct pci_dev *pdev)
{
	int pos, ret;

	ret = __ht_create_irq(pdev, 0, ipath_ht_irq_update);
	if (ret < 0) {
		ipath_dev_err(dd, "Couldn't create interrupt handler: "
			      "err %d\n", ret);
		goto bail;
	}
	dd->ipath_irq = ret;
	ret = 0;

	/*
	 * Handle clearing CRC errors in linkctrl register if necessary.  We
	 * do this early, before we ever enable errors or hardware errors,
	 * mostly to avoid causing the chip to enter freeze mode.
	 */
	pos = pci_find_capability(pdev, PCI_CAP_ID_HT);
	if (!pos) {
		ipath_dev_err(dd, "Couldn't find HyperTransport "
			      "capability; no interrupts\n");
		ret = -ENODEV;
		goto bail;
	}
	do {
		u8 cap_type;

		/*
		 * The HT capability type byte is 3 bytes after the
		 * capability byte.
		 */
		if (pci_read_config_byte(pdev, pos + 3, &cap_type)) {
			dev_info(&pdev->dev, "Couldn't read config "
				 "command @ %d\n", pos);
			continue;
		}
		if (!(cap_type & 0xE0))
			slave_or_pri_blk(dd, pdev, pos, cap_type);
	} while ((pos = pci_find_next_capability(pdev, pos,
						 PCI_CAP_ID_HT)));

	dd->ipath_flags |= IPATH_SWAP_PIOBUFS;

bail:
	return ret;
}