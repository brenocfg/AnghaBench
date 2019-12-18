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
typedef  size_t mdns_if_t ;
typedef  int /*<<< orphan*/  esp_netif_t ;

/* Variables and functions */
 size_t MDNS_IF_MAX ; 
 int /*<<< orphan*/ ** s_esp_netifs ; 

esp_netif_t *_mdns_get_esp_netif(mdns_if_t tcpip_if)
{
    if (tcpip_if < MDNS_IF_MAX) {
        return s_esp_netifs[tcpip_if];
    }
    return NULL;
}