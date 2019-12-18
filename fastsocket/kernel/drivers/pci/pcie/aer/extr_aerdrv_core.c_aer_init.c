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
struct pcie_device {int /*<<< orphan*/  port; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ forceload ; 
 int /*<<< orphan*/  pcie_aer_force_firmware_first (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int aer_init(struct pcie_device *dev)
{
	if (forceload) {
		dev_printk(KERN_DEBUG, &dev->device,
			   "aerdrv forceload requested.\n");
		pcie_aer_force_firmware_first(dev->port, 0);
	}
	return 0;
}