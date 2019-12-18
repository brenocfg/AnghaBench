#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8_t ;
struct TYPE_6__ {int addr; } ;
struct TYPE_5__ {int addr; } ;
struct netif {int flags; TYPE_2__ netmask; TYPE_1__ ip_addr; } ;
struct ip_addr {int addr; } ;
struct TYPE_8__ {int addr; } ;
struct TYPE_7__ {int addr; } ;

/* Variables and functions */
 int NETIF_FLAG_BROADCAST ; 
 TYPE_4__ ip_addr_any ; 
 TYPE_3__ ip_addr_broadcast ; 
 scalar_t__ ip_addr_netcmp (struct ip_addr*,TYPE_1__*,TYPE_2__*) ; 

u8_t ip_addr_isbroadcast(struct ip_addr *addr, struct netif *netif)
{
  /* all ones (broadcast) or all zeroes (old skool broadcast) */
  if ((addr->addr == ip_addr_broadcast.addr) ||
      (addr->addr == ip_addr_any.addr))
    return 1;
  /* no broadcast support on this network interface? */
  else if ((netif->flags & NETIF_FLAG_BROADCAST) == 0)
    /* the given address cannot be a broadcast address
     * nor can we check against any broadcast addresses */
    return 0;
  /* address matches network interface address exactly? => no broadcast */
  else if (addr->addr == netif->ip_addr.addr)
    return 0;
  /*  on the same (sub) network... */
  else if (ip_addr_netcmp(addr, &(netif->ip_addr), &(netif->netmask))
         /* ...and host identifier bits are all ones? =>... */
          && ((addr->addr & ~netif->netmask.addr) ==
           (ip_addr_broadcast.addr & ~netif->netmask.addr)))
    /* => network broadcast address */
    return 1;
  else
    return 0;
}