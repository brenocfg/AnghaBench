#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct qlcnic_adapter {int flags; int max_drv_tx_rings; int max_sds_rings; TYPE_1__* ahw; TYPE_2__* msix_entries; struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct msix_entry {int dummy; } ;
struct TYPE_5__ {int entry; } ;
struct TYPE_4__ {int num_msix; scalar_t__ msix_supported; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int QLCNIC_MSIX_ENABLED ; 
 int QLCNIC_MSI_ENABLED ; 
 int QLCNIC_TX_INTR_SHARED ; 
 int QLC_83XX_MINIMUM_VECTOR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_2__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int pci_enable_msix (struct pci_dev*,TYPE_2__*,int) ; 
 scalar_t__ qlcnic_83xx_check (struct qlcnic_adapter*) ; 
 int rounddown_pow_of_two (int) ; 

int qlcnic_enable_msix(struct qlcnic_adapter *adapter, u32 num_msix)
{
	struct pci_dev *pdev = adapter->pdev;
	int err = -1, i;
	int max_tx_rings, tx_vector;

	if (adapter->flags & QLCNIC_TX_INTR_SHARED) {
		max_tx_rings = 0;
		tx_vector = 0;
	} else {
		max_tx_rings = adapter->max_drv_tx_rings;
		tx_vector = 1;
	}

	if (!adapter->msix_entries) {
		adapter->msix_entries = kcalloc(num_msix,
						sizeof(struct msix_entry),
						GFP_KERNEL);
		if (!adapter->msix_entries) {
			dev_err(&pdev->dev, "failed allocating msix_entries\n");
			return -ENOMEM;
		}
	}

	adapter->max_sds_rings = 1;
	adapter->flags &= ~(QLCNIC_MSI_ENABLED | QLCNIC_MSIX_ENABLED);

	if (adapter->ahw->msix_supported) {
 enable_msix:
		for (i = 0; i < num_msix; i++)
			adapter->msix_entries[i].entry = i;
		err = pci_enable_msix(pdev, adapter->msix_entries, num_msix);
		if (err == 0) {
			adapter->flags |= QLCNIC_MSIX_ENABLED;
			if (qlcnic_83xx_check(adapter)) {
				adapter->ahw->num_msix = num_msix;
				/* subtract mail box and tx ring vectors */
				adapter->max_sds_rings = num_msix -
							 max_tx_rings - 1;
			} else {
				adapter->max_sds_rings = num_msix;
			}
			dev_info(&pdev->dev, "using msi-x interrupts\n");
			return err;
		} else if (err > 0) {
			dev_info(&pdev->dev,
				 "Unable to allocate %d MSI-X interrupt vectors\n",
				 num_msix);
			if (qlcnic_83xx_check(adapter)) {
				if (err < (QLC_83XX_MINIMUM_VECTOR - tx_vector))
					return err;
				err -= (max_tx_rings + 1);
				num_msix = rounddown_pow_of_two(err);
				num_msix += (max_tx_rings + 1);
			} else {
				num_msix = rounddown_pow_of_two(err);
			}

			if (num_msix) {
				dev_info(&pdev->dev,
					 "Trying to allocate %d MSI-X interrupt vectors\n",
					 num_msix);
				goto enable_msix;
			}
		} else {
			dev_info(&pdev->dev,
				 "Unable to allocate %d MSI-X interrupt vectors\n",
				 num_msix);
		}
	}

	return err;
}