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
struct pl061_gpio {unsigned int irq_base; int /*<<< orphan*/  irq_lock; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ GPIOIE ; 
 struct pl061_gpio* get_irq_chip_data (unsigned int) ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static void pl061_irq_disable(unsigned irq)
{
	struct pl061_gpio *chip = get_irq_chip_data(irq);
	int offset = irq - chip->irq_base;
	unsigned long flags;
	u8 gpioie;

	spin_lock_irqsave(&chip->irq_lock, flags);
	gpioie = readb(chip->base + GPIOIE);
	gpioie &= ~(1 << offset);
	writeb(gpioie, chip->base + GPIOIE);
	spin_unlock_irqrestore(&chip->irq_lock, flags);
}