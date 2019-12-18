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
 int /*<<< orphan*/  GPIO_MODE_INPUT ; 
 int /*<<< orphan*/  SD_TEST_BOARD_VSEL_EN_GPIO ; 
 int /*<<< orphan*/  SD_TEST_BOARD_VSEL_GPIO ; 
 int /*<<< orphan*/  gpio_set_direction (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_level (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sd_test_board_power_off(void)
{
    gpio_set_level(SD_TEST_BOARD_VSEL_EN_GPIO, 0);
    gpio_set_direction(SD_TEST_BOARD_VSEL_GPIO, GPIO_MODE_INPUT);
    gpio_set_level(SD_TEST_BOARD_VSEL_GPIO, 0);
    gpio_set_direction(SD_TEST_BOARD_VSEL_EN_GPIO, GPIO_MODE_INPUT);
}