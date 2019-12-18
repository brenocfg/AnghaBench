#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * status; } ;
typedef  TYPE_1__ rmt_channel_status_result_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  TickType_t ;
struct TYPE_5__ {int /*<<< orphan*/ * tx_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  RMT_CHANNEL_BUSY ; 
 int /*<<< orphan*/  RMT_CHANNEL_IDLE ; 
 int RMT_CHANNEL_MAX ; 
 int /*<<< orphan*/  RMT_CHANNEL_UNINIT ; 
 int /*<<< orphan*/  RMT_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RMT_PARAM_ERR_STR ; 
 TYPE_3__** p_rmt_obj ; 
 scalar_t__ pdTRUE ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ *) ; 
 scalar_t__ xSemaphoreTake (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

esp_err_t rmt_get_channel_status(rmt_channel_status_result_t *channel_status)
{
    RMT_CHECK(channel_status != NULL, RMT_PARAM_ERR_STR, ESP_ERR_INVALID_ARG);
    for(int i = 0; i < RMT_CHANNEL_MAX; i++) {
        channel_status->status[i]= RMT_CHANNEL_UNINIT;
        if( p_rmt_obj[i] != NULL ) {
            if( p_rmt_obj[i]->tx_sem != NULL ) {
                if( xSemaphoreTake(p_rmt_obj[i]->tx_sem, (TickType_t)0) == pdTRUE ) {
                    channel_status->status[i] = RMT_CHANNEL_IDLE;
                    xSemaphoreGive(p_rmt_obj[i]->tx_sem);
                } else {
                    channel_status->status[i] = RMT_CHANNEL_BUSY;
                }
            }
        }
    }
    return ESP_OK;
}