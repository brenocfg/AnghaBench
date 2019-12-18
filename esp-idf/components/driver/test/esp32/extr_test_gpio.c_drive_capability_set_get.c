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
typedef  int /*<<< orphan*/  gpio_num_t ;
typedef  int /*<<< orphan*/  gpio_drive_cap_t ;
typedef  int /*<<< orphan*/  gpio_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  GPIO_DRIVE_CAP_MAX ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_INT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_config (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_get_drive_capability (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_set_drive_capability (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_io (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void drive_capability_set_get(gpio_num_t num, gpio_drive_cap_t capability)
{
    gpio_config_t pad_io = init_io(num);
    TEST_ESP_OK(gpio_config(&pad_io));
    TEST_ASSERT(gpio_set_drive_capability(num, GPIO_DRIVE_CAP_MAX) == ESP_ERR_INVALID_ARG);

    gpio_drive_cap_t cap;
    TEST_ESP_OK(gpio_set_drive_capability(num, capability));
    TEST_ESP_OK(gpio_get_drive_capability(num, &cap));
    TEST_ASSERT_EQUAL_INT(cap, capability);
}