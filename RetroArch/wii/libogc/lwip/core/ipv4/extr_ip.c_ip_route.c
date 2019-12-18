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
struct netif {int /*<<< orphan*/  netmask; int /*<<< orphan*/  ip_addr; struct netif* next; } ;
struct ip_addr {int dummy; } ;

/* Variables and functions */
 scalar_t__ ip_addr_netcmp (struct ip_addr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct netif* netif_default ; 
 struct netif* netif_list ; 

struct netif *
ip_route(struct ip_addr *dest)
{
  struct netif *netif;

  /* iterate through netifs */
  for(netif = netif_list; netif != NULL; netif = netif->next) {
    /* network mask matches? */
    if (ip_addr_netcmp(dest, &(netif->ip_addr), &(netif->netmask))) {
      /* return netif on which to forward IP packet */
      return netif;
    }
  }
  /* no matching netif found, use default netif */
  return netif_default;
}