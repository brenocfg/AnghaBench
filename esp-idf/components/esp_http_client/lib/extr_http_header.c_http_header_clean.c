#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* http_header_item_handle_t ;
typedef  int /*<<< orphan*/  http_header_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_6__ {struct TYPE_6__* value; struct TYPE_6__* key; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_1__* STAILQ_FIRST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ ) ; 
 TYPE_1__* STAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  next ; 

esp_err_t http_header_clean(http_header_handle_t header)
{
    http_header_item_handle_t item = STAILQ_FIRST(header), tmp;
    while (item != NULL) {
        tmp = STAILQ_NEXT(item, next);
        free(item->key);
        free(item->value);
        free(item);
        item = tmp;
    }
    STAILQ_INIT(header);
    return ESP_OK;
}