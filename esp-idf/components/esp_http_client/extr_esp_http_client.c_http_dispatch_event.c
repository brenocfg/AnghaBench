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
struct TYPE_6__ {int data_len; void* data; int /*<<< orphan*/  user_data; int /*<<< orphan*/  event_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* event_handler ) (TYPE_2__*) ;int /*<<< orphan*/  user_data; TYPE_2__ event; } ;
typedef  TYPE_1__ esp_http_client_t ;
typedef  TYPE_2__ esp_http_client_event_t ;
typedef  int /*<<< orphan*/  esp_http_client_event_id_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static esp_err_t http_dispatch_event(esp_http_client_t *client, esp_http_client_event_id_t event_id, void *data, int len)
{
    esp_http_client_event_t *event = &client->event;

    if (client->event_handler) {
        event->event_id = event_id;
        event->user_data = client->user_data;
        event->data = data;
        event->data_len = len;
        return client->event_handler(event);
    }
    return ESP_OK;
}