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

/* Variables and functions */
 struct uip_netif* uip_netif_default ; 

void uip_netif_setdefault(struct uip_netif *netif)
{
	uip_netif_default = netif;
}