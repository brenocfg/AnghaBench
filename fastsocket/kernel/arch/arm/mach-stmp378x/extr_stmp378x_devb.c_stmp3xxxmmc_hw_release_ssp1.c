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
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_pins ; 
 int /*<<< orphan*/  stmp3xxx_release_pin_group (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void stmp3xxxmmc_hw_release_ssp1(void)
{
	gpio_free(PINID_PWM3);
	gpio_free(PINID_PWM4);
	stmp3xxx_release_pin_group(&mmc_pins, "mmc");
}