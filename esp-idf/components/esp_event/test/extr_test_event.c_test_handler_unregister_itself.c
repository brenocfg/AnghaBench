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
 int /*<<< orphan*/  esp_event_handler_unregister_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void (*) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*)) ; 
 int /*<<< orphan*/  s_test_base1 ; 

__attribute__((used)) static void test_handler_unregister_itself(void* event_handler_arg, esp_event_base_t event_base, int32_t event_id, void* event_data)
{
    esp_event_loop_handle_t* loop = (esp_event_loop_handle_t*) event_data;
    int* unregistered = (int*) event_handler_arg;

    (*unregistered) += (event_base == s_test_base1 ? 0 : 10) + event_id + 1;

    // Unregister this handler for this event
    TEST_ASSERT_EQUAL(ESP_OK, esp_event_handler_unregister_with(*loop, event_base, event_id, test_handler_unregister_itself));
}