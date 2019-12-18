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
typedef  TYPE_1__* wifi_netif_driver_t ;
typedef  int /*<<< orphan*/  wifi_interface_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_3__ {int /*<<< orphan*/  wifi_if; } ;

/* Variables and functions */
 int /*<<< orphan*/  esp_wifi_get_mac (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

esp_err_t esp_wifi_get_if_mac(wifi_netif_driver_t ifx, uint8_t mac[6])
{
    wifi_interface_t wifi_interface = ifx->wifi_if;

    return esp_wifi_get_mac(wifi_interface, mac);
}