#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t rmt_channel_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  scalar_t__ TickType_t ;
struct TYPE_2__ {int wait_done; int /*<<< orphan*/  tx_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_TIMEOUT ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  RMT_CHANNEL_ERROR_STR ; 
 size_t RMT_CHANNEL_MAX ; 
 int /*<<< orphan*/  RMT_CHECK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RMT_DRIVER_ERROR_STR ; 
 int /*<<< orphan*/  RMT_TAG ; 
 TYPE_1__** p_rmt_obj ; 
 scalar_t__ pdTRUE ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 
 scalar_t__ xSemaphoreTake (int /*<<< orphan*/ ,scalar_t__) ; 

esp_err_t rmt_wait_tx_done(rmt_channel_t channel, TickType_t wait_time)
{
    RMT_CHECK(channel < RMT_CHANNEL_MAX, RMT_CHANNEL_ERROR_STR, ESP_ERR_INVALID_ARG);
    RMT_CHECK(p_rmt_obj[channel] != NULL, RMT_DRIVER_ERROR_STR, ESP_FAIL);
    if(xSemaphoreTake(p_rmt_obj[channel]->tx_sem, wait_time) == pdTRUE) {
        p_rmt_obj[channel]->wait_done = false;
        xSemaphoreGive(p_rmt_obj[channel]->tx_sem);
        return ESP_OK;
    }
    else {
        if (wait_time != 0) {  // Don't emit error message if just polling.
            ESP_LOGE(RMT_TAG, "Timeout on wait_tx_done");
        }
        return ESP_ERR_TIMEOUT;
    }
}