#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* esp_websocket_client_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_6__ {scalar_t__ status_bits; struct TYPE_6__* rx_buffer; struct TYPE_6__* tx_buffer; int /*<<< orphan*/  lock; int /*<<< orphan*/  transport_list; scalar_t__ event_handle; scalar_t__ run; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  esp_event_loop_delete (scalar_t__) ; 
 int /*<<< orphan*/  esp_transport_list_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_websocket_client_destroy_config (TYPE_1__*) ; 
 int /*<<< orphan*/  esp_websocket_client_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  vEventGroupDelete (scalar_t__) ; 
 int /*<<< orphan*/  vQueueDelete (int /*<<< orphan*/ ) ; 

esp_err_t esp_websocket_client_destroy(esp_websocket_client_handle_t client)
{
    if (client == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    if (client->run) {
        esp_websocket_client_stop(client);
    }
    if (client->event_handle) {
        esp_event_loop_delete(client->event_handle);
    }
    esp_websocket_client_destroy_config(client);
    esp_transport_list_destroy(client->transport_list);
    vQueueDelete(client->lock);
    free(client->tx_buffer);
    free(client->rx_buffer);
    if (client->status_bits) {
        vEventGroupDelete(client->status_bits);
    }
    free(client);
    client = NULL;
    return ESP_OK;
}