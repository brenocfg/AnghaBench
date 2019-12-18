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
struct uip_netif {int /*<<< orphan*/  netmask; int /*<<< orphan*/  ip_addr; struct uip_netif* next; } ;
struct uip_ip_addr {int dummy; } ;

/* Variables and functions */
 scalar_t__ ip_addr_netcmp (struct uip_ip_addr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct uip_netif* uip_netif_default ; 
 struct uip_netif* uip_netif_list ; 

struct uip_netif* uip_iproute(struct uip_ip_addr *dst)
{
	struct uip_netif *netif;

	for(netif=uip_netif_list;netif!=NULL;netif=netif->next) {
		if(ip_addr_netcmp(dst,&netif->ip_addr,&netif->netmask)) return netif;
	}

	return uip_netif_default;
}