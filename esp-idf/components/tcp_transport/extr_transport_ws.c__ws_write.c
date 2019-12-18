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
typedef  char uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
typedef  TYPE_1__ transport_ws_t ;
typedef  int /*<<< orphan*/  esp_transport_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int MAX_WEBSOCKET_HEADER_SIZE ; 
 int /*<<< orphan*/  TAG ; 
 int WS_SIZE16 ; 
 int WS_SIZE64 ; 
 TYPE_1__* esp_transport_get_context_data (int /*<<< orphan*/ ) ; 
 int esp_transport_poll_write (int /*<<< orphan*/ ,int) ; 
 int esp_transport_write (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  getrandom (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _ws_write(esp_transport_handle_t t, int opcode, int mask_flag, const char *b, int len, int timeout_ms)
{
    transport_ws_t *ws = esp_transport_get_context_data(t);
    char *buffer = (char *)b;
    char ws_header[MAX_WEBSOCKET_HEADER_SIZE];
    char *mask;
    int header_len = 0, i;

    int poll_write;
    if ((poll_write = esp_transport_poll_write(ws->parent, timeout_ms)) <= 0) {
        ESP_LOGE(TAG, "Error transport_poll_write");
        return poll_write;
    }
    ws_header[header_len++] = opcode;

    if (len <= 125) {
        ws_header[header_len++] = (uint8_t)(len | mask_flag);
    } else if (len < 65536) {
        ws_header[header_len++] = WS_SIZE16 | mask_flag;
        ws_header[header_len++] = (uint8_t)(len >> 8);
        ws_header[header_len++] = (uint8_t)(len & 0xFF);
    } else {
        ws_header[header_len++] = WS_SIZE64 | mask_flag;
        /* Support maximum 4 bytes length */
        ws_header[header_len++] = 0; //(uint8_t)((len >> 56) & 0xFF);
        ws_header[header_len++] = 0; //(uint8_t)((len >> 48) & 0xFF);
        ws_header[header_len++] = 0; //(uint8_t)((len >> 40) & 0xFF);
        ws_header[header_len++] = 0; //(uint8_t)((len >> 32) & 0xFF);
        ws_header[header_len++] = (uint8_t)((len >> 24) & 0xFF);
        ws_header[header_len++] = (uint8_t)((len >> 16) & 0xFF);
        ws_header[header_len++] = (uint8_t)((len >> 8) & 0xFF);
        ws_header[header_len++] = (uint8_t)((len >> 0) & 0xFF);
    }

    if (mask_flag) {
        mask = &ws_header[header_len];
        getrandom(ws_header + header_len, 4, 0);
        header_len += 4;

        for (i = 0; i < len; ++i) {
            buffer[i] = (buffer[i] ^ mask[i % 4]);
        }
    }

    if (esp_transport_write(ws->parent, ws_header, header_len, timeout_ms) != header_len) {
        ESP_LOGE(TAG, "Error write header");
        return -1;
    }
    if (len == 0) {
        return 0;
    }

    int ret = esp_transport_write(ws->parent, buffer, len, timeout_ms);
    // in case of masked transport we have to revert back to the original data, as ws layer
    // does not create its own copy of data to be sent
    if (mask_flag) {
        mask = &ws_header[header_len-4];
        for (i = 0; i < len; ++i) {
            buffer[i] = (buffer[i] ^ mask[i % 4]);
        }
    }    
    return ret;
}