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
 int /*<<< orphan*/  outb (unsigned int,unsigned long) ; 

__attribute__((used)) static inline void i8254_write(unsigned long base_address,
			       unsigned int regshift,
			       unsigned int counter_number, unsigned int count)
{
	unsigned int byte;

	if (counter_number > 2)
		return;

	byte = count & 0xff;	/*  lsb of counter value */
	outb(byte, base_address + (counter_number << regshift));
	byte = (count >> 8) & 0xff;	/*  msb of counter value */
	outb(byte, base_address + (counter_number << regshift));
}