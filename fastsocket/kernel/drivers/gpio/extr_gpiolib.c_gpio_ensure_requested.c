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
struct gpio_chip {unsigned int base; scalar_t__ request; int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  FLAG_REQUESTED ; 
 scalar_t__ WARN (int,char*,int const) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  desc_set_label (struct gpio_desc*,char*) ; 
 int /*<<< orphan*/  pr_err (char*,int const) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gpio_ensure_requested(struct gpio_desc *desc, unsigned offset)
{
	const struct gpio_chip *chip = desc->chip;
	const int gpio = chip->base + offset;

	if (WARN(test_and_set_bit(FLAG_REQUESTED, &desc->flags) == 0,
			"autorequest GPIO-%d\n", gpio)) {
		if (!try_module_get(chip->owner)) {
			pr_err("GPIO-%d: module can't be gotten \n", gpio);
			clear_bit(FLAG_REQUESTED, &desc->flags);
			/* lose */
			return -EIO;
		}
		desc_set_label(desc, "[auto]");
		/* caller must chip->request() w/o spinlock */
		if (chip->request)
			return 1;
	}
	return 0;
}