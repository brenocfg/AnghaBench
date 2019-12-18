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
 unsigned long gpio_read_raw_reg (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned long,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static int gpio_read_reg(unsigned long reg, unsigned long reg_width,
			 unsigned long field_width, unsigned long in_pos)
{
	unsigned long data, mask, pos;

	data = 0;
	mask = (1 << field_width) - 1;
	pos = reg_width - ((in_pos + 1) * field_width);

#ifdef DEBUG
	pr_info("read_reg: addr = %lx, pos = %ld, "
		"r_width = %ld, f_width = %ld\n",
		reg, pos, reg_width, field_width);
#endif

	data = gpio_read_raw_reg(reg, reg_width);
	return (data >> pos) & mask;
}