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
typedef  int u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_CAP_ID_MSIX ; 
 int PCI_MSIX_FLAGS_QSIZE ; 
 scalar_t__ PCI_MSI_FLAGS ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int pci_find_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,scalar_t__,int*) ; 

__attribute__((used)) static int bnx2x_get_num_non_def_sbs(struct pci_dev *pdev,
				     int cnic_cnt, bool is_vf)
{
	int pos, index;
	u16 control = 0;

	pos = pci_find_capability(pdev, PCI_CAP_ID_MSIX);

	/*
	 * If MSI-X is not supported - return number of SBs needed to support
	 * one fast path queue: one FP queue + SB for CNIC
	 */
	if (!pos) {
		dev_info(&pdev->dev, "no msix capability found\n");
		return 1 + cnic_cnt;
	}
	dev_info(&pdev->dev, "msix capability found\n");

	/*
	 * The value in the PCI configuration space is the index of the last
	 * entry, namely one less than the actual size of the table, which is
	 * exactly what we want to return from this function: number of all SBs
	 * without the default SB.
	 * For VFs there is no default SB, then we return (index+1).
	 */
	pci_read_config_word(pdev, pos  + PCI_MSI_FLAGS, &control);

	index = control & PCI_MSIX_FLAGS_QSIZE;

	return is_vf ? index + 1 : index;
}