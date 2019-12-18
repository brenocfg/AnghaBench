#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* wifi_netif_driver_t ;
typedef  int /*<<< orphan*/  esp_netif_t ;
struct TYPE_7__ {int /*<<< orphan*/  driver_free_rx_buffer; int /*<<< orphan*/  transmit; TYPE_2__* handle; } ;
typedef  TYPE_3__ esp_netif_driver_ifconfig_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_5__ {int /*<<< orphan*/ * netif; } ;
struct TYPE_6__ {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  esp_netif_set_driver_config (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  wifi_free ; 
 int /*<<< orphan*/  wifi_transmit ; 

__attribute__((used)) static esp_err_t wifi_driver_start(esp_netif_t * esp_netif, void * args)
{
    wifi_netif_driver_t driver = args;
    driver->base.netif = esp_netif;
    esp_netif_driver_ifconfig_t driver_ifconfig = {
            .handle =  driver,
            .transmit = wifi_transmit,
            .driver_free_rx_buffer = wifi_free
    };

    return esp_netif_set_driver_config(esp_netif, &driver_ifconfig);
}