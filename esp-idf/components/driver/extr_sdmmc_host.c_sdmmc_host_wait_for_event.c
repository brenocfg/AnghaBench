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
typedef  int /*<<< orphan*/  sdmmc_event_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_ERR_TIMEOUT ; 
 int /*<<< orphan*/  ESP_OK ; 
 int pdFALSE ; 
 int /*<<< orphan*/  s_event_queue ; 
 int xQueueReceive (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

esp_err_t sdmmc_host_wait_for_event(int tick_count, sdmmc_event_t* out_event)
{
    if (!out_event) {
        return ESP_ERR_INVALID_ARG;
    }
    if (!s_event_queue) {
        return ESP_ERR_INVALID_STATE;
    }
    int ret = xQueueReceive(s_event_queue, out_event, tick_count);
    if (ret == pdFALSE) {
        return ESP_ERR_TIMEOUT;
    }
    return ESP_OK;
}