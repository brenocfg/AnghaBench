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
typedef  int mdns_if_t ;
typedef  int /*<<< orphan*/  esp_netif_t ;

/* Variables and functions */
 int MDNS_IF_MAX ; 
 int /*<<< orphan*/ ** s_esp_netifs ; 

__attribute__((used)) static mdns_if_t _mdns_get_if_from_esp_netif(esp_netif_t *interface)
{
    for (int i=0; i<MDNS_IF_MAX; ++i) {
        if (interface == s_esp_netifs[i])
            return i;
    }
    return MDNS_IF_MAX;
}