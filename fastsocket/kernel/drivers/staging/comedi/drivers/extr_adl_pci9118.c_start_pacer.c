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
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ PCI9118_CNT1 ; 
 scalar_t__ PCI9118_CNT2 ; 
 scalar_t__ PCI9118_CNTCTRL ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void start_pacer(struct comedi_device *dev, int mode,
			unsigned int divisor1, unsigned int divisor2)
{
	outl(0x74, dev->iobase + PCI9118_CNTCTRL);
	outl(0xb4, dev->iobase + PCI9118_CNTCTRL);
/* outl(0x30, dev->iobase + PCI9118_CNTCTRL); */
	udelay(1);

	if ((mode == 1) || (mode == 2) || (mode == 4)) {
		outl(divisor2 & 0xff, dev->iobase + PCI9118_CNT2);
		outl((divisor2 >> 8) & 0xff, dev->iobase + PCI9118_CNT2);
		outl(divisor1 & 0xff, dev->iobase + PCI9118_CNT1);
		outl((divisor1 >> 8) & 0xff, dev->iobase + PCI9118_CNT1);
	}
}