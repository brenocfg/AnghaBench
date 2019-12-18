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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ledc_mode_t ;
typedef  int /*<<< orphan*/  ledc_channel_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_INT32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ledc_get_duty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ledc_set_duty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ledc_update_duty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int portTICK_RATE_MS ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

__attribute__((used)) static void timer_duty_set_get(ledc_mode_t speed_mode, ledc_channel_t channel, uint32_t duty)
{
    TEST_ESP_OK(ledc_set_duty(speed_mode, channel, duty));
    TEST_ESP_OK(ledc_update_duty(speed_mode, channel));
    vTaskDelay(1000 / portTICK_RATE_MS);
    TEST_ASSERT_EQUAL_INT32(ledc_get_duty(speed_mode, channel), duty);
}