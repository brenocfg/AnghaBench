#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* esp_http_client_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_5__ {TYPE_1__* request; } ;
struct TYPE_4__ {int /*<<< orphan*/  headers; } ;

/* Variables and functions */
 int /*<<< orphan*/  http_header_delete (int /*<<< orphan*/ ,char const*) ; 

esp_err_t esp_http_client_delete_header(esp_http_client_handle_t client, const char *key)
{
    return http_header_delete(client->request->headers, key);
}