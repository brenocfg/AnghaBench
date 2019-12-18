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
 unsigned int i8254_control_reg ; 
 int /*<<< orphan*/  outb (unsigned int,unsigned long) ; 

__attribute__((used)) static inline int i8254_load(unsigned long base_address, unsigned int regshift,
			     unsigned int counter_number, unsigned int count,
			     unsigned int mode)
{
	unsigned int byte;

	if (counter_number > 2)
		return -1;
	if (count > 0xffff)
		return -1;
	if (mode > 5)
		return -1;
	if ((mode == 2 || mode == 3) && count == 1)
		return -1;

	byte = counter_number << 6;
	byte |= 0x30;		/*  load low then high byte */
	byte |= (mode << 1);	/*  set counter mode */
	outb(byte, base_address + (i8254_control_reg << regshift));
	byte = count & 0xff;	/*  lsb of counter value */
	outb(byte, base_address + (counter_number << regshift));
	byte = (count >> 8) & 0xff;	/*  msb of counter value */
	outb(byte, base_address + (counter_number << regshift));

	return 0;
}