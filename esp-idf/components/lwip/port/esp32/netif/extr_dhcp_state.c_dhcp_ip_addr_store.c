#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct netif {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct dhcp {TYPE_1__ offered_ip_addr; } ;
typedef  int /*<<< orphan*/  nvs_handle_t ;
typedef  int /*<<< orphan*/  esp_netif_t ;

/* Variables and functions */
 int /*<<< orphan*/  DHCP_NAMESPACE ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  NVS_READWRITE ; 
 scalar_t__ VALID_NETIF_ID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * esp_netif_get_handle_from_netif_impl (void*) ; 
 int /*<<< orphan*/  esp_netif_get_ifkey (int /*<<< orphan*/ *) ; 
 struct dhcp* netif_dhcp_data (struct netif*) ; 
 int /*<<< orphan*/  nvs_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvs_commit (int /*<<< orphan*/ ) ; 
 scalar_t__ nvs_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvs_set_u32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dhcp_ip_addr_store(void *netif)
{
    nvs_handle_t nvs;
    struct netif *net = (struct netif *)netif;
    struct dhcp *dhcp = netif_dhcp_data(net);
    uint32_t ip_addr = dhcp->offered_ip_addr.addr;
    esp_netif_t *esp_netif = esp_netif_get_handle_from_netif_impl(netif);

    if(VALID_NETIF_ID(esp_netif)) {
        if (nvs_open(DHCP_NAMESPACE, NVS_READWRITE, &nvs) == ESP_OK) {
            nvs_set_u32(nvs,esp_netif_get_ifkey(esp_netif), ip_addr);
            nvs_commit(nvs);
            nvs_close(nvs);
        }
    }
}