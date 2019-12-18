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
typedef  TYPE_1__* esp_websocket_client_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_4__ {int /*<<< orphan*/  wait_timeout_ms; int /*<<< orphan*/  state; int /*<<< orphan*/  reconnect_tick_ms; int /*<<< orphan*/  transport; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  WEBSOCKET_EVENT_DISCONNECTED ; 
 int /*<<< orphan*/  WEBSOCKET_RECONNECT_TIMEOUT_MS ; 
 int /*<<< orphan*/  WEBSOCKET_STATE_WAIT_TIMEOUT ; 
 int /*<<< orphan*/  _tick_get_ms () ; 
 int /*<<< orphan*/  esp_transport_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_websocket_client_dispatch_event (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static esp_err_t esp_websocket_client_abort_connection(esp_websocket_client_handle_t client)
{
    esp_transport_close(client->transport);
    client->wait_timeout_ms = WEBSOCKET_RECONNECT_TIMEOUT_MS;
    client->reconnect_tick_ms = _tick_get_ms();
    client->state = WEBSOCKET_STATE_WAIT_TIMEOUT;
    ESP_LOGI(TAG, "Reconnect after %d ms", client->wait_timeout_ms);
    esp_websocket_client_dispatch_event(client, WEBSOCKET_EVENT_DISCONNECTED, NULL, 0);
    return ESP_OK;
}