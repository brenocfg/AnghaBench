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
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGV (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int JOB_RESET ; 
 int /*<<< orphan*/  TAG ; 
 int portTICK_RATE_MS ; 
 int s_job ; 
 int /*<<< orphan*/  sdio_slave_send_host_int (int) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

__attribute__((used)) static esp_err_t task_hostint(void)
{
    for(int i = 0; i < 8; i++) {
        ESP_LOGV(TAG, "send intr: %d", i);
        sdio_slave_send_host_int(i);
        //check reset for quick response to RESET signal
        if (s_job & JOB_RESET) break;
        vTaskDelay(500/portTICK_RATE_MS);
    }
    return ESP_OK;
}