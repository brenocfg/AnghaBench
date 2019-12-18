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
 int EINVAL ; 
 scalar_t__ GPIOIBE ; 
 scalar_t__ GPIOIEV ; 
 scalar_t__ GPIOIS ; 
 unsigned int IRQ_TYPE_EDGE_BOTH ; 
 unsigned int IRQ_TYPE_EDGE_RISING ; 
 unsigned int IRQ_TYPE_LEVEL_HIGH ; 
 unsigned int IRQ_TYPE_LEVEL_LOW ; 
 int PL061_GPIO_NR ; 
 struct pl061_gpio* get_irq_chip_data (unsigned int) ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static int pl061_irq_type(unsigned irq, unsigned trigger)
{
	struct pl061_gpio *chip = get_irq_chip_data(irq);
	int offset = irq - chip->irq_base;
	unsigned long flags;
	u8 gpiois, gpioibe, gpioiev;

	if (offset < 0 || offset > PL061_GPIO_NR)
		return -EINVAL;

	spin_lock_irqsave(&chip->irq_lock, flags);

	gpioiev = readb(chip->base + GPIOIEV);

	gpiois = readb(chip->base + GPIOIS);
	if (trigger & (IRQ_TYPE_LEVEL_HIGH | IRQ_TYPE_LEVEL_LOW)) {
		gpiois |= 1 << offset;
		if (trigger & IRQ_TYPE_LEVEL_HIGH)
			gpioiev |= 1 << offset;
		else
			gpioiev &= ~(1 << offset);
	} else
		gpiois &= ~(1 << offset);
	writeb(gpiois, chip->base + GPIOIS);

	gpioibe = readb(chip->base + GPIOIBE);
	if ((trigger & IRQ_TYPE_EDGE_BOTH) == IRQ_TYPE_EDGE_BOTH)
		gpioibe |= 1 << offset;
	else {
		gpioibe &= ~(1 << offset);
		if (trigger & IRQ_TYPE_EDGE_RISING)
			gpioiev |= 1 << offset;
		else
			gpioiev &= ~(1 << offset);
	}
	writeb(gpioibe, chip->base + GPIOIBE);

	writeb(gpioiev, chip->base + GPIOIEV);

	spin_unlock_irqrestore(&chip->irq_lock, flags);

	return 0;
}