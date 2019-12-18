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
typedef  TYPE_1__* esp_http_client_handle_t ;
struct TYPE_3__ {scalar_t__ state; scalar_t__ is_async; int /*<<< orphan*/  timeout_ms; int /*<<< orphan*/  transport; } ;

/* Variables and functions */
 int ESP_FAIL ; 
 scalar_t__ HTTP_STATE_REQ_COMPLETE_HEADER ; 
 int esp_transport_write (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 

int esp_http_client_write(esp_http_client_handle_t client, const char *buffer, int len)
{
    if (client->state < HTTP_STATE_REQ_COMPLETE_HEADER) {
        return ESP_FAIL;
    }

    int wlen = 0, widx = 0;
    while (len > 0) {
        wlen = esp_transport_write(client->transport, buffer + widx, len, client->timeout_ms);
        /* client->async_block is initialised in case of non-blocking IO, and in this case we return how
           much ever data was written by the esp_transport_write() API. */
        if (client->is_async || wlen <= 0) {
            return wlen;
        }
        widx += wlen;
        len -= wlen;
    }
    return widx;
}