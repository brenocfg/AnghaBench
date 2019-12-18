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
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  esp_event_loop_handle_t ;
typedef  int /*<<< orphan*/  esp_event_base_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_EVENT_BASE1_EV2 ; 
 int /*<<< orphan*/  esp_event_handler_register_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  s_test_base1 ; 
 int /*<<< orphan*/  test_event_simple_handler_1 ; 
 int /*<<< orphan*/  test_event_simple_handler_2 ; 
 int /*<<< orphan*/  test_event_simple_handler_3 ; 

__attribute__((used)) static void test_registration_from_handler_hdlr(void* handler_arg, esp_event_base_t base, int32_t id, void* event_arg)
{
    esp_event_loop_handle_t* loop = (esp_event_loop_handle_t*) event_arg;
    TEST_ASSERT_EQUAL(ESP_OK, esp_event_handler_register_with(*loop, s_test_base1, TEST_EVENT_BASE1_EV2, test_event_simple_handler_1, handler_arg));
    TEST_ASSERT_EQUAL(ESP_OK, esp_event_handler_register_with(*loop, s_test_base1, TEST_EVENT_BASE1_EV2, test_event_simple_handler_2, handler_arg));
    TEST_ASSERT_EQUAL(ESP_OK, esp_event_handler_register_with(*loop, s_test_base1, TEST_EVENT_BASE1_EV2, test_event_simple_handler_3, handler_arg));
}