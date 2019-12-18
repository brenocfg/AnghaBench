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
 unsigned long ctrl_inb (unsigned long) ; 
 unsigned long ctrl_inl (unsigned long) ; 
 unsigned long ctrl_inw (unsigned long) ; 
 int /*<<< orphan*/  ctrl_outb (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  ctrl_outl (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  ctrl_outw (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static void gpio_write_reg(unsigned long reg, unsigned long reg_width,
			   unsigned long field_width, unsigned long in_pos,
			   unsigned long value)
{
	unsigned long mask, pos;

	mask = (1 << field_width) - 1;
	pos = reg_width - ((in_pos + 1) * field_width);

#ifdef DEBUG
	pr_info("write_reg addr = %lx, value = %ld, pos = %ld, "
		"r_width = %ld, f_width = %ld\n",
		reg, value, pos, reg_width, field_width);
#endif

	mask = ~(mask << pos);
	value = value << pos;

	switch (reg_width) {
	case 8:
		ctrl_outb((ctrl_inb(reg) & mask) | value, reg);
		break;
	case 16:
		ctrl_outw((ctrl_inw(reg) & mask) | value, reg);
		break;
	case 32:
		ctrl_outl((ctrl_inl(reg) & mask) | value, reg);
		break;
	}
}