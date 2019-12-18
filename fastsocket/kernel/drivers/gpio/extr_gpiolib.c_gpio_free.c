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
struct gpio_desc {int /*<<< orphan*/  flags; struct gpio_chip* chip; } ;
struct gpio_chip {int /*<<< orphan*/  owner; scalar_t__ base; int /*<<< orphan*/  (* free ) (struct gpio_chip*,scalar_t__) ;scalar_t__ can_sleep; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_REQUESTED ; 
 int /*<<< orphan*/  WARN_ON (scalar_t__) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  desc_set_label (struct gpio_desc*,int /*<<< orphan*/ *) ; 
 scalar_t__ extra_checks ; 
 struct gpio_desc* gpio_desc ; 
 int /*<<< orphan*/  gpio_is_valid (unsigned int) ; 
 int /*<<< orphan*/  gpio_lock ; 
 int /*<<< orphan*/  gpio_unexport (unsigned int) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  might_sleep_if (int) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct gpio_chip*,scalar_t__) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void gpio_free(unsigned gpio)
{
	unsigned long		flags;
	struct gpio_desc	*desc;
	struct gpio_chip	*chip;

	might_sleep();

	if (!gpio_is_valid(gpio)) {
		WARN_ON(extra_checks);
		return;
	}

	gpio_unexport(gpio);

	spin_lock_irqsave(&gpio_lock, flags);

	desc = &gpio_desc[gpio];
	chip = desc->chip;
	if (chip && test_bit(FLAG_REQUESTED, &desc->flags)) {
		if (chip->free) {
			spin_unlock_irqrestore(&gpio_lock, flags);
			might_sleep_if(extra_checks && chip->can_sleep);
			chip->free(chip, gpio - chip->base);
			spin_lock_irqsave(&gpio_lock, flags);
		}
		desc_set_label(desc, NULL);
		module_put(desc->chip->owner);
		clear_bit(FLAG_REQUESTED, &desc->flags);
	} else
		WARN_ON(extra_checks);

	spin_unlock_irqrestore(&gpio_lock, flags);
}