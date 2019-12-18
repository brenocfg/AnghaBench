#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* esp_http_client_handle_t ;
struct TYPE_7__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ esp_http_buffer_t ;
struct TYPE_6__ {scalar_t__ state; TYPE_1__* response; int /*<<< orphan*/  parser_settings; int /*<<< orphan*/  parser; int /*<<< orphan*/  timeout_ms; int /*<<< orphan*/  buffer_size_rx; int /*<<< orphan*/  transport; } ;
struct TYPE_5__ {int status_code; scalar_t__ content_length; int is_chunked; TYPE_3__* buffer; } ;

/* Variables and functions */
 int ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ HTTP_STATE_REQ_COMPLETE_DATA ; 
 scalar_t__ HTTP_STATE_REQ_COMPLETE_HEADER ; 
 scalar_t__ HTTP_STATE_RES_COMPLETE_HEADER ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ esp_transport_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_parser_execute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int esp_http_client_fetch_headers(esp_http_client_handle_t client)
{
    if (client->state < HTTP_STATE_REQ_COMPLETE_HEADER) {
        return ESP_FAIL;
    }

    client->state = HTTP_STATE_REQ_COMPLETE_DATA;
    esp_http_buffer_t *buffer = client->response->buffer;
    client->response->status_code = -1;

    while (client->state < HTTP_STATE_RES_COMPLETE_HEADER) {
        buffer->len = esp_transport_read(client->transport, buffer->data, client->buffer_size_rx, client->timeout_ms);
        if (buffer->len <= 0) {
            return ESP_FAIL;
        }
        http_parser_execute(client->parser, client->parser_settings, buffer->data, buffer->len);
    }
    ESP_LOGD(TAG, "content_length = %d", client->response->content_length);
    if (client->response->content_length <= 0) {
        client->response->is_chunked = true;
        return 0;
    }
    return client->response->content_length;
}