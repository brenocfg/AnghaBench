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
typedef  TYPE_1__* esp_transport_list_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_5__ {struct TYPE_5__* error_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  esp_transport_list_clean (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

esp_err_t esp_transport_list_destroy(esp_transport_list_handle_t h)
{
    esp_transport_list_clean(h);
    free(h->error_handle);
    free(h);
    return ESP_OK;
}