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
struct TYPE_3__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ transport_ws_t ;
typedef  int /*<<< orphan*/  esp_transport_handle_t ;

/* Variables and functions */
 TYPE_1__* esp_transport_get_context_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  realloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 

void esp_transport_ws_set_path(esp_transport_handle_t t, const char *path)
{
    transport_ws_t *ws = esp_transport_get_context_data(t);
    ws->path = realloc(ws->path, strlen(path) + 1);
    strcpy(ws->path, path);
}