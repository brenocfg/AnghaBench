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
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
typedef  TYPE_1__ transport_ws_t ;
typedef  int /*<<< orphan*/  esp_transport_handle_t ;

/* Variables and functions */
 TYPE_1__* esp_transport_get_context_data (int /*<<< orphan*/ ) ; 
 int esp_transport_poll_read (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ws_poll_read(esp_transport_handle_t t, int timeout_ms)
{
    transport_ws_t *ws = esp_transport_get_context_data(t);
    return esp_transport_poll_read(ws->parent, timeout_ms);
}