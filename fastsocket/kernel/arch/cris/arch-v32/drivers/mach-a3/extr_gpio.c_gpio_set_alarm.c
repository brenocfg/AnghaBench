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
struct gpio_private {int minor; int highalarm; int lowalarm; } ;

/* Variables and functions */
 int GPIO_MINOR_LEDS ; 
 int I2C_INTERRUPT_BITS ; 
 int REG_RD_INT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR_INT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gio ; 
 int /*<<< orphan*/  gpio_lock ; 
 int /*<<< orphan*/  regi_gio ; 
 int regk_gio_hi ; 
 int regk_gio_lo ; 
 int /*<<< orphan*/  rw_intr_cfg ; 
 int /*<<< orphan*/  rw_intr_mask ; 
 int /*<<< orphan*/  rw_intr_pins ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int wanted_interrupts ; 

__attribute__((used)) static void gpio_set_alarm(struct gpio_private *priv)
{
	int bit;
	int intr_cfg;
	int mask;
	int pins;
	unsigned long flags;

	spin_lock_irqsave(&gpio_lock, flags);
	intr_cfg = REG_RD_INT(gio, regi_gio, rw_intr_cfg);
	pins = REG_RD_INT(gio, regi_gio, rw_intr_pins);
	mask = REG_RD_INT(gio, regi_gio, rw_intr_mask) & I2C_INTERRUPT_BITS;

	for (bit = 0; bit < 32; bit++) {
		int intr = bit % 8;
		int pin = bit / 8;
		if (priv->minor < GPIO_MINOR_LEDS)
			pin += priv->minor * 4;
		else
			pin += (priv->minor - 1) * 4;

		if (priv->highalarm & (1<<bit)) {
			intr_cfg |= (regk_gio_hi << (intr * 3));
			mask |= 1 << intr;
			wanted_interrupts = mask & 0xff;
			pins |= pin << (intr * 4);
		} else if (priv->lowalarm & (1<<bit)) {
			intr_cfg |= (regk_gio_lo << (intr * 3));
			mask |= 1 << intr;
			wanted_interrupts = mask & 0xff;
			pins |= pin << (intr * 4);
		}
	}

	REG_WR_INT(gio, regi_gio, rw_intr_cfg, intr_cfg);
	REG_WR_INT(gio, regi_gio, rw_intr_pins, pins);
	REG_WR_INT(gio, regi_gio, rw_intr_mask, mask);

	spin_unlock_irqrestore(&gpio_lock, flags);
}