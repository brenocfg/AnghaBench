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

/* Variables and functions */
 scalar_t__ I8254_CTRL ; 
 unsigned int inb (unsigned int) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static unsigned int i8254_read_channel_low(unsigned int base, int chan)
{
	unsigned int msb, lsb;

	/* The following instructions must be in order.
	   We must avoid other process reading the counter's value in the
	   middle.
	   The spin_lock isn't needed since ioctl calls grab the big kernel
	   lock automatically */
	/*spin_lock(sp); */
	outb(chan << 6, base + I8254_CTRL);
	base += chan;
	lsb = inb(base);
	msb = inb(base);
	/*spin_unlock(sp); */

	return lsb | (msb << 8);
}