#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct comedi_device {int dummy; } ;
typedef  scalar_t__ resource_size_t ;
struct TYPE_2__ {int /*<<< orphan*/  io_addr; scalar_t__ phys_addr; int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DT3000_SIZE ; 
 int ENOMEM ; 
 int comedi_pci_enable (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  ioremap (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,unsigned long long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int setup_pci(struct comedi_device *dev)
{
	resource_size_t addr;
	int ret;

	ret = comedi_pci_enable(devpriv->pci_dev, "dt3000");
	if (ret < 0)
		return ret;

	addr = pci_resource_start(devpriv->pci_dev, 0);
	devpriv->phys_addr = addr;
	devpriv->io_addr = ioremap(devpriv->phys_addr, DT3000_SIZE);
	if (!devpriv->io_addr)
		return -ENOMEM;
#if DEBUG
	printk("0x%08llx mapped to %p, ",
	       (unsigned long long)devpriv->phys_addr, devpriv->io_addr);
#endif

	return 0;
}