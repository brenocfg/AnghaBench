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
struct pcie_port_service_driver {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_for_each_child (int /*<<< orphan*/ *,struct pcie_port_service_driver**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_aer_service_iter ; 

__attribute__((used)) static struct pcie_port_service_driver *find_aer_service(struct pci_dev *dev)
{
	struct pcie_port_service_driver *drv = NULL;

	device_for_each_child(&dev->dev, &drv, find_aer_service_iter);

	return drv;
}