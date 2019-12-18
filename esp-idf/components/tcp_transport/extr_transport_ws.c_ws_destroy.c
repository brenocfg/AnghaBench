#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* sub_protocol; struct TYPE_4__* path; struct TYPE_4__* buffer; } ;
typedef  TYPE_1__ transport_ws_t ;
typedef  int /*<<< orphan*/  esp_transport_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 TYPE_1__* esp_transport_get_context_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static esp_err_t ws_destroy(esp_transport_handle_t t)
{
    transport_ws_t *ws = esp_transport_get_context_data(t);
    free(ws->buffer);
    free(ws->path);
    free(ws->sub_protocol);
    free(ws);
    return 0;
}