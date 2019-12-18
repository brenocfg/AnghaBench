#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ mdns_if_t ;
struct TYPE_6__ {scalar_t__ addr; } ;
struct TYPE_7__ {TYPE_1__ ip; } ;
typedef  TYPE_2__ esp_netif_ip_info_t ;
struct TYPE_8__ {scalar_t__ addr; } ;
typedef  TYPE_3__ esp_ip4_addr_t ;

/* Variables and functions */
 scalar_t__ MDNS_IF_MAX ; 
 int /*<<< orphan*/  _mdns_dup_interface (scalar_t__) ; 
 int /*<<< orphan*/  _mdns_get_esp_netif (scalar_t__) ; 
 scalar_t__ _mdns_get_other_if (scalar_t__) ; 
 scalar_t__ esp_netif_get_ip_info (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int _mdns_check_a_collision(esp_ip4_addr_t * ip, mdns_if_t tcpip_if)
{
    esp_netif_ip_info_t if_ip_info;
    esp_netif_ip_info_t other_ip_info;
    if (!ip->addr) {
        return 1;//denial! they win
    }
    if (esp_netif_get_ip_info(_mdns_get_esp_netif(tcpip_if), &if_ip_info)) {
        return 1;//they win
    }

    int ret = memcmp((uint8_t*)&if_ip_info.ip.addr, (uint8_t*)&ip->addr, sizeof(esp_ip4_addr_t));
    if (ret > 0) {
        return -1;//we win
    } else if (ret < 0) {
        //is it the other interface?
        mdns_if_t other_if = _mdns_get_other_if (tcpip_if);
        if (other_if == MDNS_IF_MAX) {
            return 1;//AP interface! They win
        }
        if (esp_netif_get_ip_info(_mdns_get_esp_netif(other_if), &other_ip_info)) {
            return 1;//IPv4 not active! They win
        }
        if (ip->addr != other_ip_info.ip.addr) {
            return 1;//IPv4 not ours! They win
        }
        _mdns_dup_interface(tcpip_if);
        return 2;//they win
    }
    return 0;//same
}