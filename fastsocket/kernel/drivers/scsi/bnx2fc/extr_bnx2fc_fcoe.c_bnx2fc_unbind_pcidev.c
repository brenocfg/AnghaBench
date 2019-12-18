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
struct bnx2fc_hba {char* chip_num; int /*<<< orphan*/ * pcidev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_dev_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnx2fc_unbind_pcidev(struct bnx2fc_hba *hba)
{
	if (hba->pcidev) {
		hba->chip_num[0] = '\0';
		pci_dev_put(hba->pcidev);
	}
	hba->pcidev = NULL;
}