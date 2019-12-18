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
 int /*<<< orphan*/  CHECK_VALUE ; 
 int /*<<< orphan*/  ESP_RST_INT_WDT ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_HEX32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_reset_reason () ; 
 int /*<<< orphan*/  s_rtc_noinit_val ; 

__attribute__((used)) static void check_reset_reason_int_wdt(void)
{
    TEST_ASSERT_EQUAL(ESP_RST_INT_WDT, esp_reset_reason());
    TEST_ASSERT_EQUAL_HEX32(CHECK_VALUE, s_rtc_noinit_val);
}