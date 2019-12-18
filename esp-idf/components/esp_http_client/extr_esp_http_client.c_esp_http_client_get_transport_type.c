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
typedef  int /*<<< orphan*/  esp_http_client_transport_t ;
typedef  TYPE_2__* esp_http_client_handle_t ;
struct TYPE_4__ {int /*<<< orphan*/  scheme; } ;
struct TYPE_5__ {TYPE_1__ connection_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_TRANSPORT_OVER_SSL ; 
 int /*<<< orphan*/  HTTP_TRANSPORT_OVER_TCP ; 
 int /*<<< orphan*/  HTTP_TRANSPORT_UNKNOWN ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char*) ; 

esp_http_client_transport_t esp_http_client_get_transport_type(esp_http_client_handle_t client)
{
    if (!strcasecmp(client->connection_info.scheme, "https") ) {
        return HTTP_TRANSPORT_OVER_SSL;
    } else if (!strcasecmp(client->connection_info.scheme, "http")) {
        return HTTP_TRANSPORT_OVER_TCP;
    } else {
        return HTTP_TRANSPORT_UNKNOWN;
    }
}