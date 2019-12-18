#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ws_transport_opcodes_t ;
typedef  TYPE_1__* esp_websocket_client_handle_t ;
typedef  int /*<<< orphan*/  TickType_t ;
struct TYPE_4__ {int buffer_size; int /*<<< orphan*/  lock; scalar_t__ tx_buffer; int /*<<< orphan*/ * transport; } ;

/* Variables and functions */
 int ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  errno ; 
 int esp_transport_ws_send_raw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_websocket_client_is_connected (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,int) ; 
 scalar_t__ pdPASS ; 
 int /*<<< orphan*/  xSemaphoreGiveRecursive (int /*<<< orphan*/ ) ; 
 scalar_t__ xSemaphoreTakeRecursive (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int esp_websocket_client_send_with_opcode(esp_websocket_client_handle_t client, ws_transport_opcodes_t opcode, const char *data, int len, TickType_t timeout)
{
    int need_write = len;
    int wlen = 0, widx = 0;
    int ret = ESP_FAIL;

    if (client == NULL || data == NULL || len <= 0) {
        ESP_LOGE(TAG, "Invalid arguments");
        return ESP_FAIL;
    }

    if (xSemaphoreTakeRecursive(client->lock, timeout) != pdPASS) {
        ESP_LOGE(TAG, "Could not lock ws-client within %d timeout", timeout);
        return ESP_FAIL;
    }

    if (!esp_websocket_client_is_connected(client)) {
        ESP_LOGE(TAG, "Websocket client is not connected");
        goto unlock_and_return;
    }

    if (client->transport == NULL) {
        ESP_LOGE(TAG, "Invalid transport");
        goto unlock_and_return;
    }


    while (widx < len) {
        if (need_write > client->buffer_size) {
            need_write = client->buffer_size;
        }
        memcpy(client->tx_buffer, data + widx, need_write);
        // send with ws specific way and specific opcode
        wlen = esp_transport_ws_send_raw(client->transport, opcode, (char *)client->tx_buffer, need_write, timeout);
        if (wlen <= 0) {
            ret = wlen;
            ESP_LOGE(TAG, "Network error: esp_transport_write() returned %d, errno=%d", ret, errno);
            goto unlock_and_return;
        }
        widx += wlen;
        need_write = len - widx;
    }
    ret = widx;
unlock_and_return:
    xSemaphoreGiveRecursive(client->lock);
    return ret;
}