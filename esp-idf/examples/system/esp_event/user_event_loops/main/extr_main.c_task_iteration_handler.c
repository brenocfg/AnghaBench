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
typedef  int /*<<< orphan*/  esp_event_base_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  TAG ; 
 void* loop_with_task ; 

__attribute__((used)) static void task_iteration_handler(void* handler_args, esp_event_base_t base, int32_t id, void* event_data)
{
    // Two types of data can be passed in to the event handler: the handler specific data and the event-specific data.
    //
    // The handler specific data (handler_args) is a pointer to the original data, therefore, the user should ensure that
    // the memory location it points to is still valid when the handler executes.
    //
    // The event-specific data (event_data) is a pointer to a deep copy of the original data, and is managed automatically.
    int iteration = *((int*) event_data);

    char* loop;

    if (handler_args == loop_with_task) {
        loop = "loop_with_task";
    } else {
        loop = "loop_without_task";
    }

    ESP_LOGI(TAG, "handling %s:%s from %s, iteration %d", base, "TASK_ITERATION_EVENT", loop, iteration);
}