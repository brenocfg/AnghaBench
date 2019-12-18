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
typedef  int u32 ;

/* Variables and functions */
 int EFAULT ; 
 int GPIO_BIT (int) ; 
 int PIO_VA_BASE ; 
 int __raw_readl (int) ; 

__attribute__((used)) static inline int gpio_read_bit(u32 reg, int gpio)
{
	u32 bit, val;
	int ret = -EFAULT;

	if (gpio < 0)
		goto out;

	bit = GPIO_BIT(gpio);
	if (bit) {
		val = __raw_readl(PIO_VA_BASE + reg);
		ret = (val & bit) ? 1 : 0;
	}
out:
	return ret;
}