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
struct netif {int flags; int /*<<< orphan*/  ts; } ;

/* Variables and functions */
 int NETIF_FLAG_ETHARP ; 
 int NETIF_FLAG_UP ; 
 int /*<<< orphan*/  NETIF_STATUS_CALLBACK (struct netif*) ; 
 int /*<<< orphan*/  etharp_cleanup_netif (struct netif*) ; 
 int /*<<< orphan*/  snmp_get_sysuptime (int /*<<< orphan*/ *) ; 

void netif_set_down(struct netif *netif)
{
  if (netif == NULL) {	
    return;
  }

  if (netif->flags & NETIF_FLAG_UP) {
    netif->flags &= ~NETIF_FLAG_UP;
#if LWIP_SNMP
    snmp_get_sysuptime(&netif->ts);
#endif

#if LWIP_ARP
    if (netif->flags & NETIF_FLAG_ETHARP) {
      etharp_cleanup_netif(netif);
    }
#endif /* LWIP_ARP */
    NETIF_STATUS_CALLBACK(netif);
  }
}