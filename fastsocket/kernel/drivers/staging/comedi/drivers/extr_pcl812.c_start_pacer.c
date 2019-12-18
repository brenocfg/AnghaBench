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
 scalar_t__ PCL812_CTR1 ; 
 scalar_t__ PCL812_CTR2 ; 
 scalar_t__ PCL812_CTRCTL ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void start_pacer(struct comedi_device *dev, int mode,
			unsigned int divisor1, unsigned int divisor2)
{
#ifdef PCL812_EXTDEBUG
	printk("pcl812 EDBG: BGN: start_pacer(%d,%u,%u)\n", mode, divisor1,
	       divisor2);
#endif
	outb(0xb4, dev->iobase + PCL812_CTRCTL);
	outb(0x74, dev->iobase + PCL812_CTRCTL);
	udelay(1);

	if (mode == 1) {
		outb(divisor2 & 0xff, dev->iobase + PCL812_CTR2);
		outb((divisor2 >> 8) & 0xff, dev->iobase + PCL812_CTR2);
		outb(divisor1 & 0xff, dev->iobase + PCL812_CTR1);
		outb((divisor1 >> 8) & 0xff, dev->iobase + PCL812_CTR1);
	}
#ifdef PCL812_EXTDEBUG
	printk("pcl812 EDBG: END: start_pacer(...)\n");
#endif
}