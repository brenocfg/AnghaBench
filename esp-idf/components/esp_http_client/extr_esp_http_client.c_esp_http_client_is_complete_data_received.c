#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* esp_http_client_handle_t ;
struct TYPE_5__ {TYPE_1__* response; int /*<<< orphan*/  is_chunk_complete; } ;
struct TYPE_4__ {scalar_t__ data_process; scalar_t__ content_length; scalar_t__ is_chunked; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  TAG ; 

bool esp_http_client_is_complete_data_received(esp_http_client_handle_t client)
{
    if (client->response->is_chunked) {
        if (!client->is_chunk_complete) {
            ESP_LOGI(TAG, "Chunks were not completely read");
            return false;
        }
    } else {
        if (client->response->data_process != client->response->content_length) {
            ESP_LOGI(TAG, "Data processed %d != Data specified in content length %d", client->response->data_process, client->response->content_length);
            return false;
        }
    }
    return true;
}