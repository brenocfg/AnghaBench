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
typedef  int /*<<< orphan*/  esp_log_level_t ;
typedef  TYPE_2__* esp_http_client_handle_t ;
struct TYPE_7__ {int raw_len; int raw_data; char* output_ptr; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ esp_http_buffer_t ;
struct TYPE_6__ {int buffer_size_rx; int /*<<< orphan*/  parser_settings; int /*<<< orphan*/  parser; TYPE_1__* response; int /*<<< orphan*/  timeout_ms; int /*<<< orphan*/  transport; int /*<<< orphan*/  is_chunk_complete; } ;
struct TYPE_5__ {int /*<<< orphan*/  is_chunked; int /*<<< orphan*/  content_length; int /*<<< orphan*/  data_process; TYPE_3__* buffer; } ;

/* Variables and functions */
 scalar_t__ ENOTCONN ; 
 int ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,int,int,int,...) ; 
 int /*<<< orphan*/  ESP_LOG_DEBUG ; 
 int /*<<< orphan*/  ESP_LOG_LEVEL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  ESP_LOG_WARN ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ errno ; 
 int esp_transport_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_parser_execute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (char*,int,int) ; 

int esp_http_client_read(esp_http_client_handle_t client, char *buffer, int len)
{
    esp_http_buffer_t *res_buffer = client->response->buffer;

    int rlen = ESP_FAIL, ridx = 0;
    if (res_buffer->raw_len) {
        int remain_len = client->response->buffer->raw_len;
        if (remain_len > len) {
            remain_len = len;
        }
        memcpy(buffer, res_buffer->raw_data, remain_len);
        res_buffer->raw_len -= remain_len;
        res_buffer->raw_data += remain_len;
        ridx = remain_len;
    }
    int need_read = len - ridx;
    bool is_data_remain = true;
    while (need_read > 0 && is_data_remain) {
        if (client->response->is_chunked) {
            is_data_remain = !client->is_chunk_complete;
        } else {
            is_data_remain = client->response->data_process < client->response->content_length;
        }
        ESP_LOGD(TAG, "is_data_remain=%d, is_chunked=%d, content_length=%d", is_data_remain, client->response->is_chunked, client->response->content_length);
        if (!is_data_remain) {
            break;
        }
        int byte_to_read = need_read;
        if (byte_to_read > client->buffer_size_rx) {
            byte_to_read = client->buffer_size_rx;
        }
        errno = 0;
        rlen = esp_transport_read(client->transport, res_buffer->data, byte_to_read, client->timeout_ms);
        ESP_LOGD(TAG, "need_read=%d, byte_to_read=%d, rlen=%d, ridx=%d", need_read, byte_to_read, rlen, ridx);

        if (rlen <= 0) {
            if (errno != 0) {
                esp_log_level_t sev = ESP_LOG_WARN;
                /* On connection close from server, recv should ideally return 0 but we have error conversion
                 * in `tcp_transport` SSL layer which translates it `-1` and hence below additional checks */
                if (rlen == -1 && errno == ENOTCONN && client->response->is_chunked) {
                    /* Explicit call to parser for invoking `message_complete` callback */
                    http_parser_execute(client->parser, client->parser_settings, res_buffer->data, 0);
                    /* ...and lowering the message severity, as closed connection from server side is expected in chunked transport */
                    sev = ESP_LOG_DEBUG;
                }
                ESP_LOG_LEVEL(sev, TAG, "esp_transport_read returned:%d and errno:%d ", rlen, errno);
            }
            return ridx;
        }
        res_buffer->output_ptr = buffer + ridx;
        http_parser_execute(client->parser, client->parser_settings, res_buffer->data, rlen);
        ridx += res_buffer->raw_len;
        need_read -= res_buffer->raw_len;

        res_buffer->raw_len = 0; //clear
        res_buffer->output_ptr = NULL;
    }

    return ridx;
}