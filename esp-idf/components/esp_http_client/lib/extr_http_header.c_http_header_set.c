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
struct TYPE_3__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_header_delete (int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__* http_header_get_item (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  http_header_new_item (int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  http_utils_trim_whitespace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strdup (char const*) ; 

esp_err_t http_header_set(http_header_handle_t header, const char *key, const char *value)
{
    http_header_item_handle_t item;

    if (value == NULL) {
        return http_header_delete(header, key);
    }

    item = http_header_get_item(header, key);

    if (item) {
        free(item->value);
        item->value = strdup(value);
        http_utils_trim_whitespace(&item->value);
        return ESP_OK;
    }
    return http_header_new_item(header, key, value);
}