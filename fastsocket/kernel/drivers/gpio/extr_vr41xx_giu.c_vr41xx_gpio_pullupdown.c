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
typedef  int u16 ;
typedef  scalar_t__ gpio_pull_t ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  GIUTERMUPDN ; 
 int /*<<< orphan*/  GIUUSEUPDN ; 
 int GPIO_HAS_PULLUPDOWN_IO ; 
 scalar_t__ GPIO_PULL_DOWN ; 
 scalar_t__ GPIO_PULL_UP ; 
 int giu_flags ; 
 int /*<<< orphan*/  giu_lock ; 
 int giu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  giu_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int vr41xx_gpio_pullupdown(unsigned int pin, gpio_pull_t pull)
{
	u16 reg, mask;
	unsigned long flags;

	if ((giu_flags & GPIO_HAS_PULLUPDOWN_IO) != GPIO_HAS_PULLUPDOWN_IO)
		return -EPERM;

	if (pin >= 15)
		return -EINVAL;

	mask = 1 << pin;

	spin_lock_irqsave(&giu_lock, flags);

	if (pull == GPIO_PULL_UP || pull == GPIO_PULL_DOWN) {
		reg = giu_read(GIUTERMUPDN);
		if (pull == GPIO_PULL_UP)
			reg |= mask;
		else
			reg &= ~mask;
		giu_write(GIUTERMUPDN, reg);

		reg = giu_read(GIUUSEUPDN);
		reg |= mask;
		giu_write(GIUUSEUPDN, reg);
	} else {
		reg = giu_read(GIUUSEUPDN);
		reg &= ~mask;
		giu_write(GIUUSEUPDN, reg);
	}

	spin_unlock_irqrestore(&giu_lock, flags);

	return 0;
}