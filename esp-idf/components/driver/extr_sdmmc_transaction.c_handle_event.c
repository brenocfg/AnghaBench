#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sdmmc_req_state_t ;
struct TYPE_9__ {int /*<<< orphan*/  dma_status; int /*<<< orphan*/  sdmmc_status; } ;
typedef  TYPE_1__ sdmmc_event_t ;
struct TYPE_10__ {int timeout_ms; } ;
typedef  TYPE_2__ sdmmc_command_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_ERR_TIMEOUT ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ESP_LOGV (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int portTICK_PERIOD_MS ; 
 int /*<<< orphan*/  process_events (TYPE_1__,TYPE_2__*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  sdmmc_host_dma_stop () ; 
 scalar_t__ sdmmc_host_wait_for_event (int,TYPE_1__*) ; 

__attribute__((used)) static esp_err_t handle_event(sdmmc_command_t* cmd, sdmmc_req_state_t* state,
        sdmmc_event_t* unhandled_events)
{
    sdmmc_event_t event;
    esp_err_t err = sdmmc_host_wait_for_event(cmd->timeout_ms / portTICK_PERIOD_MS, &event);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "sdmmc_host_wait_for_event returned 0x%x", err);
        if (err == ESP_ERR_TIMEOUT) {
            sdmmc_host_dma_stop();
        }
        return err;
    }
    ESP_LOGV(TAG, "sdmmc_handle_event: event %08x %08x, unhandled %08x %08x",
            event.sdmmc_status, event.dma_status,
            unhandled_events->sdmmc_status, unhandled_events->dma_status);
    event.sdmmc_status |= unhandled_events->sdmmc_status;
    event.dma_status |= unhandled_events->dma_status;
    process_events(event, cmd, state, unhandled_events);
    ESP_LOGV(TAG, "sdmmc_handle_event: events unhandled: %08x %08x", unhandled_events->sdmmc_status, unhandled_events->dma_status);
    return ESP_OK;
}