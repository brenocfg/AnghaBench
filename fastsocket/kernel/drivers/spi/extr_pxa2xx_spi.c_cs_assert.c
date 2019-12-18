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
struct driver_data {struct chip_data* cur_chip; } ;
struct chip_data {int /*<<< orphan*/  gpio_cs_inverted; int /*<<< orphan*/  gpio_cs; int /*<<< orphan*/  (* cs_control ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PXA2XX_CS_ASSERT ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cs_assert(struct driver_data *drv_data)
{
	struct chip_data *chip = drv_data->cur_chip;

	if (chip->cs_control) {
		chip->cs_control(PXA2XX_CS_ASSERT);
		return;
	}

	if (gpio_is_valid(chip->gpio_cs))
		gpio_set_value(chip->gpio_cs, chip->gpio_cs_inverted);
}