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
struct comedi_device {scalar_t__ iobase; } ;
struct TYPE_2__ {int da_ranges; int* ao_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*) ; 
 scalar_t__ PCI1720_DA0 ; 
 scalar_t__ PCI1720_DA1 ; 
 scalar_t__ PCI1720_DA2 ; 
 scalar_t__ PCI1720_DA3 ; 
 scalar_t__ PCI1720_RANGE ; 
 scalar_t__ PCI1720_SYNCONT ; 
 scalar_t__ PCI1720_SYNCOUT ; 
 int Syncont_SC0 ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static int pci1720_reset(struct comedi_device *dev)
{
	DPRINTK("adv_pci1710 EDBG: BGN: pci1720_reset(...)\n");
	outb(Syncont_SC0, dev->iobase + PCI1720_SYNCONT);	/*  set synchronous output mode */
	devpriv->da_ranges = 0xAA;
	outb(devpriv->da_ranges, dev->iobase + PCI1720_RANGE);	/*  set all ranges to +/-5V */
	outw(0x0800, dev->iobase + PCI1720_DA0);	/*  set outputs to 0V */
	outw(0x0800, dev->iobase + PCI1720_DA1);
	outw(0x0800, dev->iobase + PCI1720_DA2);
	outw(0x0800, dev->iobase + PCI1720_DA3);
	outb(0, dev->iobase + PCI1720_SYNCOUT);	/*  update outputs */
	devpriv->ao_data[0] = 0x0800;
	devpriv->ao_data[1] = 0x0800;
	devpriv->ao_data[2] = 0x0800;
	devpriv->ao_data[3] = 0x0800;
	DPRINTK("adv_pci1710 EDBG: END: pci1720_reset(...)\n");
	return 0;
}