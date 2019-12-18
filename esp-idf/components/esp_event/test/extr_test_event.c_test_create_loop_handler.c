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
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  esp_event_loop_handle_t ;
typedef  int /*<<< orphan*/  esp_event_loop_args_t ;
typedef  int /*<<< orphan*/  esp_event_base_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_EVENT_BASE1_EV1 ; 
 int /*<<< orphan*/  esp_event_loop_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_event_loop_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_event_get_default_loop_args () ; 

__attribute__((used)) static void test_create_loop_handler(void* handler_args, esp_event_base_t base, int32_t id, void* event_data)
{
    esp_event_loop_args_t loop_args = test_event_get_default_loop_args();

    if (id == TEST_EVENT_BASE1_EV1) {
        TEST_ASSERT_EQUAL(ESP_OK, esp_event_loop_create(&loop_args, (esp_event_loop_handle_t*) handler_args));
    } else {
        TEST_ASSERT_EQUAL(ESP_OK, esp_event_loop_delete(*((esp_event_loop_handle_t*) handler_args)));
    }
}