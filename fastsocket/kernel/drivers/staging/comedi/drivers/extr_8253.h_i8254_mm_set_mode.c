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
 unsigned int I8254_BINARY ; 
 unsigned int I8254_MODE5 ; 
 unsigned int i8254_control_reg ; 
 int /*<<< orphan*/  writeb (unsigned int,void*) ; 

__attribute__((used)) static inline int i8254_mm_set_mode(void *base_address,
				    unsigned int regshift,
				    unsigned int counter_number,
				    unsigned int mode)
{
	unsigned int byte;

	if (counter_number > 2)
		return -1;
	if (mode > (I8254_MODE5 | I8254_BINARY))
		return -1;

	byte = counter_number << 6;
	byte |= 0x30;		/*  load low then high byte */
	byte |= mode;		/*  set counter mode and BCD|binary */
	writeb(byte, base_address + (i8254_control_reg << regshift));

	return 0;
}