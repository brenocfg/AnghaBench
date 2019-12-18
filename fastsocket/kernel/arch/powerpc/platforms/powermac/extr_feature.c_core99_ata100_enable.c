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
typedef  int /*<<< orphan*/  u8 ;
struct pci_dev {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 long ENODEV ; 
 int /*<<< orphan*/  LOCK (unsigned long) ; 
 int /*<<< orphan*/  UNI_N_CLOCK_CNTL ; 
 int /*<<< orphan*/  UNI_N_CLOCK_CNTL_ATA100 ; 
 int /*<<< orphan*/  UNLOCK (unsigned long) ; 
 int /*<<< orphan*/  UN_BIC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UN_BIS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UN_IN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 scalar_t__ pci_device_from_OF_node (struct device_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pci_enable_device (struct pci_dev*) ; 
 struct pci_dev* pci_get_bus_and_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int uninorth_rev ; 

__attribute__((used)) static long
core99_ata100_enable(struct device_node *node, long value)
{
	unsigned long flags;
	struct pci_dev *pdev = NULL;
	u8 pbus, pid;
	int rc;

	if (uninorth_rev < 0x24)
		return -ENODEV;

	LOCK(flags);
	if (value)
		UN_BIS(UNI_N_CLOCK_CNTL, UNI_N_CLOCK_CNTL_ATA100);
	else
		UN_BIC(UNI_N_CLOCK_CNTL, UNI_N_CLOCK_CNTL_ATA100);
	(void)UN_IN(UNI_N_CLOCK_CNTL);
	UNLOCK(flags);
	udelay(20);

	if (value) {
		if (pci_device_from_OF_node(node, &pbus, &pid) == 0)
			pdev = pci_get_bus_and_slot(pbus, pid);
		if (pdev == NULL)
			return 0;
		rc = pci_enable_device(pdev);
		if (rc == 0)
			pci_set_master(pdev);
		pci_dev_put(pdev);
		if (rc)
			return rc;
	}
	return 0;
}