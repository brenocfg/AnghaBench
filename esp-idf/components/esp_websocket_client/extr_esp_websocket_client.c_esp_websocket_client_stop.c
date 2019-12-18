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
typedef  TYPE_1__* esp_websocket_client_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_3__ {int run; int /*<<< orphan*/  state; int /*<<< orphan*/  status_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  STOPPED_BIT ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  WEBSOCKET_STATE_UNKNOW ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  xEventGroupWaitBits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

esp_err_t esp_websocket_client_stop(esp_websocket_client_handle_t client)
{
    if (client == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    if (!client->run) {
        ESP_LOGW(TAG, "Client was not started");
        return ESP_FAIL;
    }
    client->run = false;
    xEventGroupWaitBits(client->status_bits, STOPPED_BIT, false, true, portMAX_DELAY);
    client->state = WEBSOCKET_STATE_UNKNOW;
    return ESP_OK;
}