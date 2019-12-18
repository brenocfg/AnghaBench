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
 int ENODEV ; 
 int /*<<< orphan*/  find_msi_translator (struct pci_dev*) ; 

__attribute__((used)) static int axon_msi_check_device(struct pci_dev *dev, int nvec, int type)
{
	if (!find_msi_translator(dev))
		return -ENODEV;

	return 0;
}