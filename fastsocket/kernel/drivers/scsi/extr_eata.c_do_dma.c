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
typedef  unsigned char unchar ;

/* Variables and functions */
 unsigned long H2DEV (unsigned long) ; 
 int MAXLOOP ; 
 scalar_t__ REG_CMD ; 
 scalar_t__ REG_LM ; 
 scalar_t__ REG_LOW ; 
 scalar_t__ REG_MID ; 
 scalar_t__ REG_MSB ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 
 scalar_t__ wait_on_busy (unsigned long,int) ; 

__attribute__((used)) static int do_dma(unsigned long iobase, unsigned long addr, unchar cmd)
{
	unsigned char *byaddr;
	unsigned long devaddr;

	if (wait_on_busy(iobase, (addr ? MAXLOOP * 100 : MAXLOOP)))
		return 1;

	if (addr) {
		devaddr = H2DEV(addr);
		byaddr = (unsigned char *)&devaddr;
		outb(byaddr[3], iobase + REG_LOW);
		outb(byaddr[2], iobase + REG_LM);
		outb(byaddr[1], iobase + REG_MID);
		outb(byaddr[0], iobase + REG_MSB);
	}

	outb(cmd, iobase + REG_CMD);
	return 0;
}