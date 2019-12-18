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
 scalar_t__ PCL816_CLRINT ; 
 scalar_t__ PCL816_CONTROL ; 
 scalar_t__ PCL816_CTRCTL ; 
 scalar_t__ PCL816_MUX ; 
 scalar_t__ PCL816_RANGE ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static void pcl816_reset(struct comedi_device *dev)
{
/* outb (0, dev->iobase + PCL818_DA_LO);         DAC=0V */
/* outb (0, dev->iobase + PCL818_DA_HI); */
/* udelay (1); */
/* outb (0, dev->iobase + PCL818_DO_HI);        DO=$0000 */
/* outb (0, dev->iobase + PCL818_DO_LO); */
/* udelay (1); */
	outb(0, dev->iobase + PCL816_CONTROL);
	outb(0, dev->iobase + PCL816_MUX);
	outb(0, dev->iobase + PCL816_CLRINT);
	outb(0xb0, dev->iobase + PCL816_CTRCTL);	/* Stop pacer */
	outb(0x70, dev->iobase + PCL816_CTRCTL);
	outb(0x30, dev->iobase + PCL816_CTRCTL);
	outb(0, dev->iobase + PCL816_RANGE);
}