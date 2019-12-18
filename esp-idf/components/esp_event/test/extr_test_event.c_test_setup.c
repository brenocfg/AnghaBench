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
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_TRUE (int) ; 
 int TEST_CONFIG_TASKS_TO_SPAWN ; 
 int /*<<< orphan*/  esp_event_loop_create_default () ; 

__attribute__((used)) static void test_setup(void)
{
    TEST_ASSERT_TRUE(TEST_CONFIG_TASKS_TO_SPAWN >= 2);
    TEST_ASSERT_EQUAL(ESP_OK, esp_event_loop_create_default());
}