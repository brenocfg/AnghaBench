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
struct qe_gpio_chip {int /*<<< orphan*/  lock; } ;
struct of_mm_gpio_chip {int /*<<< orphan*/  regs; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QE_PIO_DIR_IN ; 
 int /*<<< orphan*/  __par_io_config_pin (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct of_mm_gpio_chip* to_of_mm_gpio_chip (struct gpio_chip*) ; 
 struct qe_gpio_chip* to_qe_gpio_chip (struct of_mm_gpio_chip*) ; 

__attribute__((used)) static int qe_gpio_dir_in(struct gpio_chip *gc, unsigned int gpio)
{
	struct of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	struct qe_gpio_chip *qe_gc = to_qe_gpio_chip(mm_gc);
	unsigned long flags;

	spin_lock_irqsave(&qe_gc->lock, flags);

	__par_io_config_pin(mm_gc->regs, gpio, QE_PIO_DIR_IN, 0, 0, 0);

	spin_unlock_irqrestore(&qe_gc->lock, flags);

	return 0;
}