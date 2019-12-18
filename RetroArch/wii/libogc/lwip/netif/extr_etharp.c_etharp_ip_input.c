#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pbuf {struct ethip_hdr* payload; } ;
struct netif {int /*<<< orphan*/  netmask; int /*<<< orphan*/  ip_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  src; } ;
struct TYPE_4__ {int /*<<< orphan*/  src; } ;
struct ethip_hdr {TYPE_1__ eth; TYPE_2__ ip; } ;

/* Variables and functions */
 int DBG_TRACE ; 
 int ETHARP_DEBUG ; 
 int /*<<< orphan*/  LWIP_ASSERT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int,char*) ; 
 int /*<<< orphan*/  ip_addr_netcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_arp_entry (struct netif*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
etharp_ip_input(struct netif *netif, struct pbuf *p)
{
  struct ethip_hdr *hdr;
  LWIP_ASSERT("netif != NULL", netif != NULL);
  /* Only insert an entry if the source IP address of the
     incoming IP packet comes from a host on the local network. */
  hdr = p->payload;
  /* source is not on the local network? */
  if (!ip_addr_netcmp(&(hdr->ip.src), &(netif->ip_addr), &(netif->netmask))) {
    /* do nothing */
    return;
  }

  LWIP_DEBUGF(ETHARP_DEBUG | DBG_TRACE, ("etharp_ip_input: updating ETHARP table.\n"));
  /* update ARP table */
  /* @todo We could use ETHARP_TRY_HARD if we think we are going to talk
   * back soon (for example, if the destination IP address is ours. */
  update_arp_entry(netif, &(hdr->ip.src), &(hdr->eth.src), 0);
}