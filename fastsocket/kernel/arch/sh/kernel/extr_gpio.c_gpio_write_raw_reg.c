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
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  ctrl_outb (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  ctrl_outl (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  ctrl_outw (unsigned long,unsigned long) ; 

__attribute__((used)) static void gpio_write_raw_reg(unsigned long reg,
			       unsigned long reg_width,
			       unsigned long data)
{
	switch (reg_width) {
	case 8:
		ctrl_outb(data, reg);
		return;
	case 16:
		ctrl_outw(data, reg);
		return;
	case 32:
		ctrl_outl(data, reg);
		return;
	}

	BUG();
}