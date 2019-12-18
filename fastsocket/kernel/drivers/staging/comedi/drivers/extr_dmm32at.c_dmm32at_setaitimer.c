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
struct comedi_device {int dummy; } ;

/* Variables and functions */
 unsigned char DMM32AT_ADINT ; 
 int /*<<< orphan*/  DMM32AT_CLK1 ; 
 int /*<<< orphan*/  DMM32AT_CLK2 ; 
 unsigned char DMM32AT_CLKACC ; 
 int /*<<< orphan*/  DMM32AT_CLKCT ; 
 unsigned char DMM32AT_CLKCT1 ; 
 unsigned char DMM32AT_CLKCT2 ; 
 unsigned char DMM32AT_CLKSEL ; 
 int /*<<< orphan*/  DMM32AT_CNTRDIO ; 
 int /*<<< orphan*/  DMM32AT_CNTRL ; 
 int /*<<< orphan*/  DMM32AT_INTCLOCK ; 
 int /*<<< orphan*/  dmm_outb (struct comedi_device*,int /*<<< orphan*/ ,unsigned char) ; 

void dmm32at_setaitimer(struct comedi_device *dev, unsigned int nansec)
{
	unsigned char lo1, lo2, hi2;
	unsigned short both2;

	/* based on 10mhz clock */
	lo1 = 200;
	both2 = nansec / 20000;
	hi2 = (both2 & 0xff00) >> 8;
	lo2 = both2 & 0x00ff;

	/* set the counter frequency to 10mhz */
	dmm_outb(dev, DMM32AT_CNTRDIO, 0);

	/* get access to the clock regs */
	dmm_outb(dev, DMM32AT_CNTRL, DMM32AT_CLKACC);

	/* write the counter 1 control word and low byte to counter */
	dmm_outb(dev, DMM32AT_CLKCT, DMM32AT_CLKCT1);
	dmm_outb(dev, DMM32AT_CLK1, lo1);

	/* write the counter 2 control word and low byte then to counter */
	dmm_outb(dev, DMM32AT_CLKCT, DMM32AT_CLKCT2);
	dmm_outb(dev, DMM32AT_CLK2, lo2);
	dmm_outb(dev, DMM32AT_CLK2, hi2);

	/* enable the ai conversion interrupt and the clock to start scans */
	dmm_outb(dev, DMM32AT_INTCLOCK, DMM32AT_ADINT | DMM32AT_CLKSEL);

}