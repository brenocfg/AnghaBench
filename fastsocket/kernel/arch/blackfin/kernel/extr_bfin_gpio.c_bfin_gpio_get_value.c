#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int data; } ;

/* Variables and functions */
 int get_gpio_data (unsigned int) ; 
 int /*<<< orphan*/  get_gpio_edge (unsigned int) ; 
 TYPE_1__** gpio_array ; 
 size_t gpio_bank (unsigned int) ; 
 int gpio_sub_n (unsigned int) ; 
 int /*<<< orphan*/  local_irq_restore_hw (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save_hw (unsigned long) ; 
 int /*<<< orphan*/  set_gpio_edge (unsigned int,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int bfin_gpio_get_value(unsigned gpio)
{
#ifdef CONFIG_BF54x
	return (1 & (gpio_array[gpio_bank(gpio)]->data >> gpio_sub_n(gpio)));
#else
	unsigned long flags;

	if (unlikely(get_gpio_edge(gpio))) {
		int ret;
		local_irq_save_hw(flags);
		set_gpio_edge(gpio, 0);
		ret = get_gpio_data(gpio);
		set_gpio_edge(gpio, 1);
		local_irq_restore_hw(flags);
		return ret;
	} else
		return get_gpio_data(gpio);
#endif
}