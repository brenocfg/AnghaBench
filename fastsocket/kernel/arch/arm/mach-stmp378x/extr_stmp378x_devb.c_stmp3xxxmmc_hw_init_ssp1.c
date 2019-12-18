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

/* Variables and functions */
 int /*<<< orphan*/  PINID_PWM3 ; 
 int /*<<< orphan*/  PINID_PWM4 ; 
 int /*<<< orphan*/  gpio_direction_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mmc_pins ; 
 int /*<<< orphan*/  stmp3xxx_release_pin_group (int /*<<< orphan*/ *,char*) ; 
 int stmp3xxx_request_pin_group (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int stmp3xxxmmc_hw_init_ssp1(void)
{
	int ret;

	ret = stmp3xxx_request_pin_group(&mmc_pins, "mmc");
	if (ret)
		goto out;

	/* Configure write protect GPIO pin */
	ret = gpio_request(PINID_PWM4, "mmc wp");
	if (ret)
		goto out_wp;

	gpio_direction_input(PINID_PWM4);

	/* Configure POWER pin as gpio to drive power to MMC slot */
	ret = gpio_request(PINID_PWM3, "mmc power");
	if (ret)
		goto out_power;

	gpio_direction_output(PINID_PWM3, 0);
	mdelay(100);

	return 0;

out_power:
	gpio_free(PINID_PWM4);
out_wp:
	stmp3xxx_release_pin_group(&mmc_pins, "mmc");
out:
	return ret;
}