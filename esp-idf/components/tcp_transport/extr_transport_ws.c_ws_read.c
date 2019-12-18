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
struct TYPE_3__ {char read_opcode; int /*<<< orphan*/  parent; } ;
typedef  TYPE_1__ transport_ws_t ;
typedef  int /*<<< orphan*/  esp_transport_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int MAX_WEBSOCKET_HEADER_SIZE ; 
 int /*<<< orphan*/  TAG ; 
 TYPE_1__* esp_transport_get_context_data (int /*<<< orphan*/ ) ; 
 int esp_transport_poll_read (int /*<<< orphan*/ ,int) ; 
 int esp_transport_read (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static int ws_read(esp_transport_handle_t t, char *buffer, int len, int timeout_ms)
{
    transport_ws_t *ws = esp_transport_get_context_data(t);
    int payload_len;
    char ws_header[MAX_WEBSOCKET_HEADER_SIZE];
    char *data_ptr = ws_header, mask, *mask_key = NULL;
    int rlen;
    int poll_read;
    if ((poll_read = esp_transport_poll_read(ws->parent, timeout_ms)) <= 0) {
        return poll_read;
    }

    // Receive and process header first (based on header size)
    int header = 2;
    if ((rlen = esp_transport_read(ws->parent, data_ptr, header, timeout_ms)) <= 0) {
        ESP_LOGE(TAG, "Error read data");
        return rlen;
    }
    ws->read_opcode = (*data_ptr & 0x0F);
    data_ptr ++;
    mask = ((*data_ptr >> 7) & 0x01);
    payload_len = (*data_ptr & 0x7F);
    data_ptr++;
    ESP_LOGD(TAG, "Opcode: %d, mask: %d, len: %d\r\n", ws->read_opcode, mask, payload_len);
    if (payload_len == 126) {
        // headerLen += 2;
        if ((rlen = esp_transport_read(ws->parent, data_ptr, header, timeout_ms)) <= 0) {
            ESP_LOGE(TAG, "Error read data");
            return rlen;
        }
        payload_len = data_ptr[0] << 8 | data_ptr[1];
    } else if (payload_len == 127) {
        // headerLen += 8;
        header = 8;
        if ((rlen = esp_transport_read(ws->parent, data_ptr, header, timeout_ms)) <= 0) {
            ESP_LOGE(TAG, "Error read data");
            return rlen;
        }

        if (data_ptr[0] != 0 || data_ptr[1] != 0 || data_ptr[2] != 0 || data_ptr[3] != 0) {
            // really too big!
            payload_len = 0xFFFFFFFF;
        } else {
            payload_len = data_ptr[4] << 24 | data_ptr[5] << 16 | data_ptr[6] << 8 | data_ptr[7];
        }
    }

    if (payload_len > len) {
        ESP_LOGD(TAG, "Actual data to receive (%d) are longer than ws buffer (%d)", payload_len, len);
        payload_len = len;
    }

    // Then receive and process payload
    if (payload_len != 0 && (rlen = esp_transport_read(ws->parent, buffer, payload_len, timeout_ms)) <= 0) {
        ESP_LOGE(TAG, "Error read data");
        return rlen;
    }

    if (mask) {
        mask_key = buffer;
        data_ptr = buffer + 4;
        for (int i = 0; i < payload_len; i++) {
            buffer[i] = (data_ptr[i] ^ mask_key[i % 4]);
        }
    }
    return payload_len;
}