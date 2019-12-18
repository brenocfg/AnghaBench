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
struct TYPE_3__ {char* post_data; int post_len; } ;

/* Variables and functions */

int esp_http_client_get_post_field(esp_http_client_handle_t client, char **data)
{
    if (client->post_data) {
        *data = client->post_data;
        return client->post_len;
    }
    return 0;
}