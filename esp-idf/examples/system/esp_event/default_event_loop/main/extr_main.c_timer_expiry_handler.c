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
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  TIMER ; 
 int /*<<< orphan*/  TIMER_EVENTS ; 
 int /*<<< orphan*/  TIMER_EVENT_STOPPED ; 
 int TIMER_EXPIRIES_COUNT ; 
 int /*<<< orphan*/  esp_event_post (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_timer_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_id_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portMAX_DELAY ; 

__attribute__((used)) static void timer_expiry_handler(void* handler_args, esp_event_base_t base, int32_t id, void* event_data)
{
    static int count = 0;

    count++;

    if (count >= TIMER_EXPIRIES_COUNT) {
        // Stop the timer
        ESP_ERROR_CHECK(esp_timer_stop(TIMER));

        ESP_LOGI(TAG, "%s:%s: posting to default loop", base, get_id_string(base, TIMER_EVENT_STOPPED));

        // Post the event that the timer has been stopped
        ESP_ERROR_CHECK(esp_event_post(TIMER_EVENTS, TIMER_EVENT_STOPPED, NULL, 0, portMAX_DELAY));
    }

    ESP_LOGI(TAG, "%s:%s: timer_expiry_handler, executed %d out of %d times", base, get_id_string(base, id), count, TIMER_EXPIRIES_COUNT);
}