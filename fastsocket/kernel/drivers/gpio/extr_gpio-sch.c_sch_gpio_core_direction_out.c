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
typedef  int u8 ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 unsigned int CGIO ; 
 scalar_t__ gpio_ba ; 
 int /*<<< orphan*/  gpio_lock ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  sch_gpio_core_set (struct gpio_chip*,unsigned int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sch_gpio_core_direction_out(struct gpio_chip *gc,
					unsigned gpio_num, int val)
{
	u8 curr_dirs;
	unsigned short offset, bit;

	sch_gpio_core_set(gc, gpio_num, val);

	spin_lock(&gpio_lock);

	offset = CGIO + gpio_num / 8;
	bit = gpio_num % 8;

	curr_dirs = inb(gpio_ba + offset);
	if (curr_dirs & (1 << bit))
		outb(curr_dirs & ~(1 << bit), gpio_ba + offset);

	spin_unlock(&gpio_lock);
	return 0;
}