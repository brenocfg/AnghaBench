#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* wifi_netif_driver_t ;
typedef  int /*<<< orphan*/  wifi_interface_t ;
struct wifi_netif_driver {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  post_attach; } ;
struct TYPE_6__ {TYPE_1__ base; int /*<<< orphan*/  wifi_if; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAG ; 
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/  wifi_driver_start ; 

wifi_netif_driver_t esp_wifi_create_if_driver(wifi_interface_t wifi_if)
{
    wifi_netif_driver_t driver = calloc(1, sizeof(struct wifi_netif_driver));
    if (driver == NULL) {
        ESP_LOGE(TAG, "No memory to create a wifi interface handle");
        return NULL;
    }
    driver->wifi_if = wifi_if;
    driver->base.post_attach = wifi_driver_start;
    return driver;
}