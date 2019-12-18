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
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int device_for_each_child (int /*<<< orphan*/ *,struct pcie_device**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_aer_device_iter ; 

__attribute__((used)) static int find_aer_device(struct pci_dev *dev, struct pcie_device **result)
{
	return device_for_each_child(&dev->dev, result, find_aer_device_iter);
}