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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  esp_timer_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  esp_timer_get_time () ; 
 int /*<<< orphan*/  esp_timer_start_periodic (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  esp_timer_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void oneshot_timer_callback(void* arg)
{
    int64_t time_since_boot = esp_timer_get_time();
    ESP_LOGI(TAG, "One-shot timer called, time since boot: %lld us", time_since_boot);
    esp_timer_handle_t periodic_timer_handle = (esp_timer_handle_t) arg;
    /* To start the timer which is running, need to stop it first */
    ESP_ERROR_CHECK(esp_timer_stop(periodic_timer_handle));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer_handle, 1000000));
    time_since_boot = esp_timer_get_time();
    ESP_LOGI(TAG, "Restarted periodic timer with 1s period, time since boot: %lld us",
            time_since_boot);
}