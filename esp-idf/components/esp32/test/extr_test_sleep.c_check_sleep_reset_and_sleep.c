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
 int /*<<< orphan*/  ESP_RST_DEEPSLEEP ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_deep_sleep_start () ; 
 int /*<<< orphan*/  esp_reset_reason () ; 
 int /*<<< orphan*/  esp_sleep_enable_timer_wakeup (int) ; 

__attribute__((used)) static void check_sleep_reset_and_sleep(void)
{
    TEST_ASSERT_EQUAL(ESP_RST_DEEPSLEEP, esp_reset_reason());
    esp_sleep_enable_timer_wakeup(100000);
    esp_deep_sleep_start();
}