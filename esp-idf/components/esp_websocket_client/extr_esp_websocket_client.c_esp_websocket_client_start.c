#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* esp_websocket_client_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_6__ {scalar_t__ state; int /*<<< orphan*/  status_bits; TYPE_1__* config; } ;
struct TYPE_5__ {int /*<<< orphan*/  task_prio; int /*<<< orphan*/  task_stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  STOPPED_BIT ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ WEBSOCKET_STATE_INIT ; 
 int /*<<< orphan*/  esp_websocket_client_task ; 
 scalar_t__ pdTRUE ; 
 int /*<<< orphan*/  xEventGroupClearBits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xTaskCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

esp_err_t esp_websocket_client_start(esp_websocket_client_handle_t client)
{
    if (client == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    if (client->state >= WEBSOCKET_STATE_INIT) {
        ESP_LOGE(TAG, "The client has started");
        return ESP_FAIL;
    }
    if (xTaskCreate(esp_websocket_client_task, "websocket_task", client->config->task_stack, client, client->config->task_prio, NULL) != pdTRUE) {
        ESP_LOGE(TAG, "Error create websocket task");
        return ESP_FAIL;
    }
    xEventGroupClearBits(client->status_bits, STOPPED_BIT);
    return ESP_OK;
}