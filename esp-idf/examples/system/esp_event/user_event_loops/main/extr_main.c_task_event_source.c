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
typedef  scalar_t__ esp_event_loop_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  TASK_EVENTS ; 
 int TASK_ITERATIONS_COUNT ; 
 int /*<<< orphan*/  TASK_ITERATION_EVENT ; 
 int /*<<< orphan*/  TASK_PERIOD ; 
 int /*<<< orphan*/  esp_event_post_to (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ loop_with_task ; 
 scalar_t__ loop_without_task ; 
 int /*<<< orphan*/  pdMS_TO_TICKS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  vTaskDelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void task_event_source(void* args)
{
    for(int iteration = 1; iteration <= TASK_ITERATIONS_COUNT; iteration++) {
        esp_event_loop_handle_t loop_to_post_to;

        if (iteration % 2 == 0) {
            // if even, post to the event loop with dedicated task
            loop_to_post_to = loop_with_task;
        } else {
            // if odd, post to the event loop without a dedicated task
            loop_to_post_to = loop_without_task;
        }

        ESP_LOGI(TAG, "posting %s:%s to %s, iteration %d out of %d", TASK_EVENTS, "TASK_ITERATION_EVENT",
                loop_to_post_to == loop_with_task ? "loop_with_task" : "loop_without_task",
                iteration, TASK_ITERATIONS_COUNT);

        ESP_ERROR_CHECK(esp_event_post_to(loop_to_post_to, TASK_EVENTS, TASK_ITERATION_EVENT, &iteration, sizeof(iteration), portMAX_DELAY));

        vTaskDelay(pdMS_TO_TICKS(TASK_PERIOD));
    }

    vTaskDelay(pdMS_TO_TICKS(TASK_PERIOD));

    ESP_LOGI(TAG, "deleting task event source");

    vTaskDelete(NULL);
}