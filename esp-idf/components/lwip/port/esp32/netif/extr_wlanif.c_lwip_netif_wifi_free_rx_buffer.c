#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct netif {int dummy; } ;
typedef  int /*<<< orphan*/  esp_netif_t ;

/* Variables and functions */
 int /*<<< orphan*/  esp_netif_free_rx_buffer (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/ * esp_netif_get_handle_from_netif_impl (struct netif*) ; 

__attribute__((used)) static void lwip_netif_wifi_free_rx_buffer(struct netif *netif, void *buf)
{
    esp_netif_t *esp_netif = esp_netif_get_handle_from_netif_impl(netif);
    esp_netif_free_rx_buffer(esp_netif, buf);
}