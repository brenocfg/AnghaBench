#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ esp_timer_handle_t ;
struct TYPE_3__ {char* name; void* arg; int /*<<< orphan*/ * callback; } ;
typedef  TYPE_1__ esp_timer_create_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  esp_light_sleep_start () ; 
 int /*<<< orphan*/  esp_sleep_enable_timer_wakeup (int) ; 
 int /*<<< orphan*/  esp_timer_create (TYPE_1__ const*,scalar_t__*) ; 
 int /*<<< orphan*/  esp_timer_delete (scalar_t__) ; 
 int /*<<< orphan*/  esp_timer_dump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_timer_get_time () ; 
 int /*<<< orphan*/  esp_timer_start_once (scalar_t__,int) ; 
 int /*<<< orphan*/  esp_timer_start_periodic (scalar_t__,int) ; 
 int /*<<< orphan*/  esp_timer_stop (scalar_t__) ; 
 int /*<<< orphan*/  oneshot_timer_callback ; 
 int /*<<< orphan*/  periodic_timer_callback ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  usleep (int) ; 

void app_main(void)
{
    /* Create two timers:
     * 1. a periodic timer which will run every 0.5s, and print a message
     * 2. a one-shot timer which will fire after 5s, and re-start periodic
     *    timer with period of 1s.
     */

    const esp_timer_create_args_t periodic_timer_args = {
            .callback = &periodic_timer_callback,
            /* name is optional, but may help identify the timer when debugging */
            .name = "periodic"
    };

    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    /* The timer has been created but is not running yet */

    const esp_timer_create_args_t oneshot_timer_args = {
            .callback = &oneshot_timer_callback,
            /* argument specified here will be passed to timer callback function */
            .arg = (void*) periodic_timer,
            .name = "one-shot"
    };
    esp_timer_handle_t oneshot_timer;
    ESP_ERROR_CHECK(esp_timer_create(&oneshot_timer_args, &oneshot_timer));

    /* Start the timers */
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, 500000));
    ESP_ERROR_CHECK(esp_timer_start_once(oneshot_timer, 5000000));
    ESP_LOGI(TAG, "Started timers, time since boot: %lld us", esp_timer_get_time());

    /* Print debugging information about timers to console every 2 seconds */
    for (int i = 0; i < 5; ++i) {
        ESP_ERROR_CHECK(esp_timer_dump(stdout));
        usleep(2000000);
    }

    /* Timekeeping continues in light sleep, and timers are scheduled
     * correctly after light sleep.
     */
    ESP_LOGI(TAG, "Entering light sleep for 0.5s, time since boot: %lld us",
            esp_timer_get_time());

    ESP_ERROR_CHECK(esp_sleep_enable_timer_wakeup(500000));
    esp_light_sleep_start();

    ESP_LOGI(TAG, "Woke up from light sleep, time since boot: %lld us",
                esp_timer_get_time());

    /* Let the timer run for a little bit more */
    usleep(2000000);

    /* Clean up and finish the example */
    ESP_ERROR_CHECK(esp_timer_stop(periodic_timer));
    ESP_ERROR_CHECK(esp_timer_delete(periodic_timer));
    ESP_ERROR_CHECK(esp_timer_delete(oneshot_timer));
    ESP_LOGI(TAG, "Stopped and deleted timers");
}