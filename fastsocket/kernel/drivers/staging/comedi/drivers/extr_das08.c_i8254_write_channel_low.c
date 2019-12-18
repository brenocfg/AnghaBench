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
 int /*<<< orphan*/  outb (unsigned int,unsigned int) ; 

__attribute__((used)) static void i8254_write_channel_low(unsigned int base, int chan,
				    unsigned int value)
{
	unsigned int msb, lsb;

	lsb = value & 0xFF;
	msb = value >> 8;

	/* write lsb, then msb */
	base += chan;
	/* See comments in i8254_read_channel_low */
	/*spin_lock(sp); */
	outb(lsb, base);
	outb(msb, base);
	/*spin_unlock(sp); */
}