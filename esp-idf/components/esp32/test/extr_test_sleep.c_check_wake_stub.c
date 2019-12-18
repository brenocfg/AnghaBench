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

/* Variables and functions */
 int /*<<< orphan*/  ESP_RST_DEEPSLEEP ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_HEX32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_get_deep_sleep_wake_stub () ; 
 int /*<<< orphan*/  esp_reset_reason () ; 
 int /*<<< orphan*/  s_wake_stub_var ; 
 int /*<<< orphan*/  wake_stub ; 

__attribute__((used)) static void check_wake_stub(void)
{
    TEST_ASSERT_EQUAL(ESP_RST_DEEPSLEEP, esp_reset_reason());
    TEST_ASSERT_EQUAL_HEX32((uint32_t) &wake_stub, s_wake_stub_var);
    /* ROM code clears wake stub entry address */
    TEST_ASSERT_NULL(esp_get_deep_sleep_wake_stub());
}