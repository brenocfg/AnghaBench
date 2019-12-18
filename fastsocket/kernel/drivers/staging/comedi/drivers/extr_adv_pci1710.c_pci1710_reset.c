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
struct TYPE_2__ {int cardtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*) ; 
#define  TYPE_PCI1720 128 
 int pci171x_reset (struct comedi_device*) ; 
 int pci1720_reset (struct comedi_device*) ; 
 TYPE_1__* this_board ; 

__attribute__((used)) static int pci1710_reset(struct comedi_device *dev)
{
	DPRINTK("adv_pci1710 EDBG: BGN: pci1710_reset(...)\n");
	switch (this_board->cardtype) {
	case TYPE_PCI1720:
		return pci1720_reset(dev);
	default:
		return pci171x_reset(dev);
	}
	DPRINTK("adv_pci1710 EDBG: END: pci1710_reset(...)\n");
}