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
typedef  TYPE_1__* esp_transport_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_5__ {struct TYPE_5__* scheme; int /*<<< orphan*/  (* _destroy ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

esp_err_t esp_transport_destroy(esp_transport_handle_t t)
{
    if (t->_destroy) {
        t->_destroy(t);
    }
    if (t->scheme) {
        free(t->scheme);
    }
    free(t);
    return ESP_OK;
}