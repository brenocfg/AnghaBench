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
typedef  int /*<<< orphan*/  iteration ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  TASK_EVENTS ; 
 int TASK_ITERATIONS_COUNT ; 
 int TASK_ITERATIONS_UNREGISTER ; 
 int /*<<< orphan*/  TASK_ITERATION_EVENT ; 
 int /*<<< orphan*/  TASK_PERIOD ; 
 int /*<<< orphan*/  esp_event_handler_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_event_post (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_id_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdMS_TO_TICKS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  task_iteration_handler ; 
 int /*<<< orphan*/  vTaskDelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void task_event_source(void* args)
{
    for(int iteration = 1; iteration <= TASK_ITERATIONS_COUNT; iteration++) {

        ESP_LOGI(TAG, "%s:%s: posting to default loop, %d out of %d", TASK_EVENTS,
                get_id_string(TASK_EVENTS, TASK_ITERATION_EVENT), iteration, TASK_ITERATIONS_COUNT);

        // Post that the loop has iterated. Notice that the iteration count is passed to the handler. Take note
        // that data passed during event posting is a deep copy of the original data.
        ESP_ERROR_CHECK(esp_event_post(TASK_EVENTS, TASK_ITERATION_EVENT, &iteration, sizeof(iteration), portMAX_DELAY));

        if (iteration == TASK_ITERATIONS_UNREGISTER) {
            ESP_LOGI(TAG, "%s:%s: unregistering task_iteration_handler", TASK_EVENTS, get_id_string(TASK_EVENTS, TASK_ITERATION_EVENT));
            ESP_ERROR_CHECK(esp_event_handler_unregister(TASK_EVENTS, TASK_ITERATION_EVENT, task_iteration_handler));
        }

        vTaskDelay(pdMS_TO_TICKS(TASK_PERIOD));
    }

    vTaskDelay(pdMS_TO_TICKS(TASK_PERIOD));

    ESP_LOGI(TAG, "%s:%s: deleting task event source", TASK_EVENTS, get_id_string(TASK_EVENTS, TASK_ITERATION_EVENT));

    vTaskDelete(NULL);
}