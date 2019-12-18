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
struct driver_data {int dummy; } ;
struct chip_data {int flag; int /*<<< orphan*/  cs_gpio; int /*<<< orphan*/  chip_select_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int read_FLAG (struct driver_data*) ; 
 int /*<<< orphan*/  write_FLAG (struct driver_data*,int) ; 

__attribute__((used)) static void bfin_spi_cs_active(struct driver_data *drv_data, struct chip_data *chip)
{
	if (likely(chip->chip_select_num)) {
		u16 flag = read_FLAG(drv_data);

		flag |= chip->flag;
		flag &= ~(chip->flag << 8);

		write_FLAG(drv_data, flag);
	} else {
		gpio_set_value(chip->cs_gpio, 0);
	}
}