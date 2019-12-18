#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* http_header_item_handle_t ;
typedef  int /*<<< orphan*/  http_header_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_5__ {struct TYPE_5__* value; struct TYPE_5__* key; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_NOT_FOUND ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  STAILQ_REMOVE (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* http_header_get_item (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  http_header_item ; 
 int /*<<< orphan*/  next ; 

esp_err_t http_header_delete(http_header_handle_t header, const char *key)
{
    http_header_item_handle_t item = http_header_get_item(header, key);
    if (item) {
        STAILQ_REMOVE(header, item, http_header_item, next);
        free(item->key);
        free(item->value);
        free(item);
    } else {
        return ESP_ERR_NOT_FOUND;
    }
    return ESP_OK;
}