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
typedef  int /*<<< orphan*/  esp_transport_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAG ; 
 int WS_FIN ; 
 int /*<<< orphan*/  WS_MASK ; 
 int WS_OPCODE_BINARY ; 
 int WS_OPCODE_PING ; 
 int _ws_write (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char const*,int,int) ; 

__attribute__((used)) static int ws_write(esp_transport_handle_t t, const char *b, int len, int timeout_ms)
{
    if (len == 0) {
        // Default transport write of zero length in ws layer sends out a ping message.
        // This behaviour could however be altered in IDF 5.0, since a separate API for sending
        // messages with user defined opcodes has been introduced.
        ESP_LOGD(TAG, "Write PING message");
        return _ws_write(t, WS_OPCODE_PING | WS_FIN, WS_MASK, NULL, 0, timeout_ms);
    }
    return _ws_write(t, WS_OPCODE_BINARY | WS_FIN, WS_MASK, b, len, timeout_ms);
}