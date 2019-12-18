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
typedef  TYPE_1__* http_header_item_handle_t ;
typedef  int /*<<< orphan*/  http_header_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_3__ {char* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_1__* http_header_get_item (int /*<<< orphan*/ ,char const*) ; 

esp_err_t http_header_get(http_header_handle_t header, const char *key, char **value)
{
    http_header_item_handle_t item;

    item = http_header_get_item(header, key);
    if (item) {
        *value = item->value;
    } else {
        *value = NULL;
    }

    return ESP_OK;
}