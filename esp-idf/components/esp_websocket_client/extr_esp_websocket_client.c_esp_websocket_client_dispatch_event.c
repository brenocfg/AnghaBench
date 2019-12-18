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
typedef  int /*<<< orphan*/  esp_websocket_event_id_t ;
struct TYPE_5__ {char const* data_ptr; int data_len; int /*<<< orphan*/  op_code; } ;
typedef  TYPE_1__ esp_websocket_event_data_t ;
typedef  TYPE_2__* esp_websocket_client_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_6__ {int /*<<< orphan*/  event_handle; int /*<<< orphan*/  last_opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  WEBSOCKET_EVENTS ; 
 int /*<<< orphan*/  esp_event_loop_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_event_post_to (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portMAX_DELAY ; 

__attribute__((used)) static esp_err_t esp_websocket_client_dispatch_event(esp_websocket_client_handle_t client,
                                                     esp_websocket_event_id_t event,
                                                     const char *data,
                                                     int data_len)
{
    esp_err_t err;
    esp_websocket_event_data_t event_data;
    event_data.data_ptr = data;
    event_data.data_len = data_len;
    event_data.op_code = client->last_opcode;

    if ((err = esp_event_post_to(client->event_handle,
                                 WEBSOCKET_EVENTS, event,
                                 &event_data,
                                 sizeof(esp_websocket_event_data_t),
                                 portMAX_DELAY)) != ESP_OK) {
        return err;
    }
    return esp_event_loop_run(client->event_handle, 0);
}