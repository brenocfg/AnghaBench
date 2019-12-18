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
struct uip_pbuf {int dummy; } ;
struct uip_netif {int dummy; } ;
struct uip_ip_addr {int dummy; } ;
typedef  int /*<<< orphan*/  s8_t ;

/* Variables and functions */
 int /*<<< orphan*/  uip_arp_out (struct uip_netif*,struct uip_ip_addr*,struct uip_pbuf*) ; 

__attribute__((used)) static s8_t __bba_start_tx(struct uip_netif *dev,struct uip_pbuf *p,struct uip_ip_addr *ipaddr)
{
	return uip_arp_out(dev,ipaddr,p);
}