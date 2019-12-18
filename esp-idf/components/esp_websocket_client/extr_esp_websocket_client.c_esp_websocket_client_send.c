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
typedef  int /*<<< orphan*/  esp_websocket_client_handle_t ;
typedef  int /*<<< orphan*/  TickType_t ;

/* Variables and functions */
 int /*<<< orphan*/  WS_TRANSPORT_OPCODES_BINARY ; 
 int esp_websocket_client_send_with_opcode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 

int esp_websocket_client_send(esp_websocket_client_handle_t client, const char *data, int len, TickType_t timeout)
{
    return esp_websocket_client_send_with_opcode(client, WS_TRANSPORT_OPCODES_BINARY, data, len, timeout);
}