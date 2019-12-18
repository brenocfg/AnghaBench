#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ws_transport_opcodes_t ;
typedef  int uint8_t ;
typedef  int /*<<< orphan*/ * esp_transport_handle_t ;

/* Variables and functions */
 int ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAG ; 
 int WS_FIN ; 
 int /*<<< orphan*/  WS_MASK ; 
 int _ws_write (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char const*,int,int) ; 
 int ws_get_bin_opcode (int /*<<< orphan*/ ) ; 

int esp_transport_ws_send_raw(esp_transport_handle_t t, ws_transport_opcodes_t opcode, const char *b, int len, int timeout_ms)
{
    uint8_t op_code = ws_get_bin_opcode(opcode);
    if (t == NULL) {
        ESP_LOGE(TAG, "Transport must be a valid ws handle");
        return ESP_ERR_INVALID_ARG;
    }
    ESP_LOGD(TAG, "Sending raw ws message with opcode %d", op_code);
    return _ws_write(t, op_code | WS_FIN, WS_MASK, b, len, timeout_ms);
}