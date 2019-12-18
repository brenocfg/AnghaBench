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
struct netif {int dummy; } ;
struct ip4_addr {int dummy; } ;
typedef  scalar_t__ mdns_ip_protocol_t ;
typedef  int /*<<< orphan*/  mdns_if_t ;
struct TYPE_5__ {int /*<<< orphan*/  ip6; int /*<<< orphan*/  ip4; } ;
struct TYPE_6__ {TYPE_1__ u_addr; } ;
typedef  TYPE_2__ ip_addr_t ;
typedef  int /*<<< orphan*/  esp_netif_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_2__ IPADDR6_INIT (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IP_ADDR4 (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ MDNS_IP_PROTOCOL_V4 ; 
 int /*<<< orphan*/ * _mdns_get_esp_netif (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (struct netif*) ; 
 struct netif* esp_netif_get_netif_impl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_netif_is_netif_up (int /*<<< orphan*/ *) ; 
 scalar_t__ igmp_joingroup_netif (struct netif*,struct ip4_addr const*) ; 
 scalar_t__ igmp_leavegroup_netif (struct netif*,struct ip4_addr const*) ; 
 scalar_t__ mld6_joingroup_netif (struct netif*,int /*<<< orphan*/ *) ; 
 scalar_t__ mld6_leavegroup_netif (struct netif*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static esp_err_t _udp_join_group(mdns_if_t if_inx, mdns_ip_protocol_t ip_protocol, bool join)
{
    struct netif * netif = NULL;
    esp_netif_t *tcpip_if = _mdns_get_esp_netif(if_inx);

    if (!esp_netif_is_netif_up(tcpip_if)) {
        // Network interface went down before event propagated, skipping IGMP config
        return ESP_ERR_INVALID_STATE;
    }

    netif = esp_netif_get_netif_impl(tcpip_if);
    assert(netif);

    if (ip_protocol == MDNS_IP_PROTOCOL_V4) {
        ip_addr_t multicast_addr;
        IP_ADDR4(&multicast_addr, 224, 0, 0, 251);

        if(join){
            if (igmp_joingroup_netif(netif, (const struct ip4_addr *)&multicast_addr.u_addr.ip4)) {
                return ESP_ERR_INVALID_STATE;
            }
        } else {
            if (igmp_leavegroup_netif(netif, (const struct ip4_addr *)&multicast_addr.u_addr.ip4)) {
                return ESP_ERR_INVALID_STATE;
            }
        }
    } else {
        ip_addr_t multicast_addr = IPADDR6_INIT(0x000002ff, 0, 0, 0xfb000000);

        if(join){
            if (mld6_joingroup_netif(netif, &(multicast_addr.u_addr.ip6))) {
                return ESP_ERR_INVALID_STATE;
            }
        } else {
            if (mld6_leavegroup_netif(netif, &(multicast_addr.u_addr.ip6))) {
                return ESP_ERR_INVALID_STATE;
            }
        }
    }
    return ESP_OK;
}