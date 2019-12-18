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
typedef  TYPE_1__* esp_transport_list_handle_t ;
typedef  int /*<<< orphan*/ * esp_transport_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_3__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/ * STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * STAILQ_NEXT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_transport_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next ; 

esp_err_t esp_transport_list_clean(esp_transport_list_handle_t h)
{
    esp_transport_handle_t item = STAILQ_FIRST(&h->list);
    esp_transport_handle_t tmp;
    while (item != NULL) {
        tmp = STAILQ_NEXT(item, next);
        esp_transport_destroy(item);
        item = tmp;
    }
    STAILQ_INIT(&h->list);
    return ESP_OK;
}