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
typedef  int u8_t ;
struct uip_netif {int flags; } ;

/* Variables and functions */
 int UIP_NETIF_FLAG_UP ; 

u8_t uip_netif_isup(struct uip_netif *netif)
{
	return (netif->flags&UIP_NETIF_FLAG_UP);
}