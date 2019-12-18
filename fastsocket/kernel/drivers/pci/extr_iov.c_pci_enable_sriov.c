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
struct pci_dev {int /*<<< orphan*/  is_physfn; } ;

/* Variables and functions */
 int ENODEV ; 
 int EPERM ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  pci_sriov_enabled ; 
 int sriov_enable (struct pci_dev*,int) ; 

int pci_enable_sriov(struct pci_dev *dev, int nr_virtfn)
{
	might_sleep();

	if (!pci_sriov_enabled)
		return -EPERM;

	if (!dev->is_physfn)
		return -ENODEV;

	return sriov_enable(dev, nr_virtfn);
}