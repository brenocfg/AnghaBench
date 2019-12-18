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
struct pci_dev {int dummy; } ;

/* Variables and functions */
#define  ECRC_POLICY_DEFAULT 130 
#define  ECRC_POLICY_OFF 129 
#define  ECRC_POLICY_ON 128 
 int /*<<< orphan*/  disable_ecrc_checking (struct pci_dev*) ; 
 int ecrc_policy ; 
 int /*<<< orphan*/  enable_ecrc_checking (struct pci_dev*) ; 

void pcie_set_ecrc_checking(struct pci_dev *dev)
{
	switch (ecrc_policy) {
	case ECRC_POLICY_DEFAULT:
		return;
	case ECRC_POLICY_OFF:
		disable_ecrc_checking(dev);
		break;
	case ECRC_POLICY_ON:
		enable_ecrc_checking(dev);
		break;
	default:
		return;
	}
}