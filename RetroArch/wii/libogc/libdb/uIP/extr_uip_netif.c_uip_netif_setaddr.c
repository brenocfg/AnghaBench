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
struct uip_netif {int dummy; } ;
struct uip_ip_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  uip_netif_setgw (struct uip_netif*,struct uip_ip_addr*) ; 
 int /*<<< orphan*/  uip_netif_setipaddr (struct uip_netif*,struct uip_ip_addr*) ; 
 int /*<<< orphan*/  uip_netif_setnetmask (struct uip_netif*,struct uip_ip_addr*) ; 

void uip_netif_setaddr(struct uip_netif *netif,struct uip_ip_addr *ipaddr,struct uip_ip_addr *netmask,struct uip_ip_addr *gw)
{
	uip_netif_setipaddr(netif,ipaddr);
	uip_netif_setnetmask(netif,netmask);
	uip_netif_setgw(netif,gw);
}