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
typedef  int /*<<< orphan*/  protocomm_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  console_task ; 
 int /*<<< orphan*/ * pc_console ; 
 int /*<<< orphan*/  xTaskNotifyGive (int /*<<< orphan*/ ) ; 

esp_err_t protocomm_console_stop(protocomm_t *pc)
{
    if (pc != pc_console) {
        ESP_LOGE(TAG, "Incorrect stop request");
        return ESP_ERR_INVALID_ARG;
    }

    ESP_LOGI(TAG, "Stopping console...");
    xTaskNotifyGive(console_task);
    return ESP_OK;
}