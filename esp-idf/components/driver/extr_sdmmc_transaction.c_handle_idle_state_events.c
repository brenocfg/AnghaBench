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
struct TYPE_3__ {int sdmmc_status; scalar_t__ dma_status; } ;
typedef  TYPE_1__ sdmmc_event_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  ESP_LOGV (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int SDMMC_INTMASK_CD ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ sdmmc_host_wait_for_event (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static esp_err_t handle_idle_state_events(void)
{
    /* Handle any events which have happened in between transfers.
     * Under current assumptions (no SDIO support) only card detect events
     * can happen in the idle state.
     */
    sdmmc_event_t evt;
    while (sdmmc_host_wait_for_event(0, &evt) == ESP_OK) {
        if (evt.sdmmc_status & SDMMC_INTMASK_CD) {
            ESP_LOGV(TAG, "card detect event");
            evt.sdmmc_status &= ~SDMMC_INTMASK_CD;
        }
        if (evt.sdmmc_status != 0 || evt.dma_status != 0) {
            ESP_LOGE(TAG, "handle_idle_state_events unhandled: %08x %08x",
                    evt.sdmmc_status, evt.dma_status);
        }

    }
    return ESP_OK;
}