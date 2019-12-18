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
struct TYPE_2__ {scalar_t__ pci_device; scalar_t__ plx_regbase_size; scalar_t__ plx_regbase; scalar_t__ me_regbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_pci_disable (scalar_t__) ; 
 TYPE_1__* dev_private ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  me_reset (struct comedi_device*) ; 
 int /*<<< orphan*/  pci_dev_put (scalar_t__) ; 

__attribute__((used)) static int me_detach(struct comedi_device *dev)
{
	if (dev_private) {
		if (dev_private->me_regbase) {
			me_reset(dev);
			iounmap(dev_private->me_regbase);
		}
		if (dev_private->plx_regbase)
			iounmap(dev_private->plx_regbase);
		if (dev_private->pci_device) {
			if (dev_private->plx_regbase_size)
				comedi_pci_disable(dev_private->pci_device);

			pci_dev_put(dev_private->pci_device);
		}
	}
	return 0;
}