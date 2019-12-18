#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* esp_http_client_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_7__ {int /*<<< orphan*/  scheme; int /*<<< orphan*/  port; int /*<<< orphan*/  host; } ;
struct TYPE_8__ {scalar_t__ state; TYPE_1__ connection_info; int /*<<< orphan*/  timeout_ms; int /*<<< orphan*/ * transport; int /*<<< orphan*/  is_async; int /*<<< orphan*/  transport_list; } ;

/* Variables and functions */
 int ASYNC_TRANS_CONNECTING ; 
 int ASYNC_TRANS_CONNECT_FAIL ; 
 int /*<<< orphan*/  ESP_ERR_HTTP_CONNECT ; 
 int /*<<< orphan*/  ESP_ERR_HTTP_CONNECTING ; 
 int /*<<< orphan*/  ESP_ERR_HTTP_INVALID_TRANSPORT ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  HTTP_EVENT_ON_CONNECTED ; 
 scalar_t__ HTTP_STATE_CONNECTED ; 
 scalar_t__ HTTP_STATE_UNINIT ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  esp_http_client_close (TYPE_2__*) ; 
 int /*<<< orphan*/  esp_http_client_prepare (TYPE_2__*) ; 
 scalar_t__ esp_transport_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int esp_transport_connect_async (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * esp_transport_list_get_transport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_dispatch_event (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static esp_err_t esp_http_client_connect(esp_http_client_handle_t client)
{
    esp_err_t err;

    if (client->state == HTTP_STATE_UNINIT) {
        ESP_LOGE(TAG, "Client has not been initialized");
        return ESP_ERR_INVALID_STATE;
    }

    if ((err = esp_http_client_prepare(client)) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize request data");
        esp_http_client_close(client);
        return err;
    }

    if (client->state < HTTP_STATE_CONNECTED) {
        ESP_LOGD(TAG, "Begin connect to: %s://%s:%d", client->connection_info.scheme, client->connection_info.host, client->connection_info.port);
        client->transport = esp_transport_list_get_transport(client->transport_list, client->connection_info.scheme);
        if (client->transport == NULL) {
            ESP_LOGE(TAG, "No transport found");
#ifndef CONFIG_ESP_HTTP_CLIENT_ENABLE_HTTPS
            if (strcasecmp(client->connection_info.scheme, "https") == 0) {
                ESP_LOGE(TAG, "Please enable HTTPS at menuconfig to allow requesting via https");
            }
#endif
            return ESP_ERR_HTTP_INVALID_TRANSPORT;
        }
        if (!client->is_async) {
            if (esp_transport_connect(client->transport, client->connection_info.host, client->connection_info.port, client->timeout_ms) < 0) {
                ESP_LOGE(TAG, "Connection failed, sock < 0");
                return ESP_ERR_HTTP_CONNECT;
            }
        } else {
            int ret = esp_transport_connect_async(client->transport, client->connection_info.host, client->connection_info.port, client->timeout_ms);
            if (ret == ASYNC_TRANS_CONNECT_FAIL) {
                ESP_LOGE(TAG, "Connection failed");
                if (strcasecmp(client->connection_info.scheme, "http") == 0) {
                    ESP_LOGE(TAG, "Asynchronous mode doesn't work for HTTP based connection");
                    return ESP_ERR_INVALID_ARG;
                }
                return ESP_ERR_HTTP_CONNECT;
            } else if (ret == ASYNC_TRANS_CONNECTING) {
                ESP_LOGD(TAG, "Connection not yet established");
                return ESP_ERR_HTTP_CONNECTING;
            }
        }
        client->state = HTTP_STATE_CONNECTED;
        http_dispatch_event(client, HTTP_EVENT_ON_CONNECTED, NULL, 0);
    }
    return ESP_OK;
}