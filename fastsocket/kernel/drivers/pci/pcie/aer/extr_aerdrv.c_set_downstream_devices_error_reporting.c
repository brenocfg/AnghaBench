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
struct pci_dev {int /*<<< orphan*/  subordinate; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_walk_bus (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (struct pci_dev*,int*),int*) ; 
 int /*<<< orphan*/  set_device_error_reporting (struct pci_dev*,int*) ; 

__attribute__((used)) static void set_downstream_devices_error_reporting(struct pci_dev *dev,
						   bool enable)
{
	set_device_error_reporting(dev, &enable);

	if (!dev->subordinate)
		return;
	pci_walk_bus(dev->subordinate, set_device_error_reporting, &enable);
}