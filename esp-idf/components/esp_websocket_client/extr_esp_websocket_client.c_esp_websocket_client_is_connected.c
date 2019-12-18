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
typedef  TYPE_1__* esp_websocket_client_handle_t ;
struct TYPE_3__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ WEBSOCKET_STATE_CONNECTED ; 

bool esp_websocket_client_is_connected(esp_websocket_client_handle_t client)
{
    if (client == NULL) {
        return false;
    }
    return client->state == WEBSOCKET_STATE_CONNECTED;
}