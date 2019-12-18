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
struct pcie_device {int dummy; } ;
struct pci_dev {int dummy; } ;
struct aer_err_info {scalar_t__ severity; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 scalar_t__ AER_CORRECTABLE ; 
 scalar_t__ PCI_ERR_COR_STATUS ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_ERR ; 
 int /*<<< orphan*/  do_recovery (struct pci_dev*,scalar_t__) ; 
 int pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_error_source(struct pcie_device *aerdev,
	struct pci_dev *dev,
	struct aer_err_info *info)
{
	int pos;

	if (info->severity == AER_CORRECTABLE) {
		/*
		 * Correctable error does not need software intevention.
		 * No need to go through error recovery process.
		 */
		pos = pci_find_ext_capability(dev, PCI_EXT_CAP_ID_ERR);
		if (pos)
			pci_write_config_dword(dev, pos + PCI_ERR_COR_STATUS,
					info->status);
	} else
		do_recovery(dev, info->severity);
}