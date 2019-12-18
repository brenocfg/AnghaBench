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
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  rbtx4938_spi_gpio_lock ; 
 int /*<<< orphan*/  rbtx4938_spics_addr ; 
 int readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rbtx4938_spi_gpio_set(struct gpio_chip *chip, unsigned int offset,
				  int value)
{
	u8 val;
	unsigned long flags;
	spin_lock_irqsave(&rbtx4938_spi_gpio_lock, flags);
	val = readb(rbtx4938_spics_addr);
	if (value)
		val |= 1 << offset;
	else
		val &= ~(1 << offset);
	writeb(val, rbtx4938_spics_addr);
	mmiowb();
	spin_unlock_irqrestore(&rbtx4938_spi_gpio_lock, flags);
}