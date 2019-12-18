#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8_t ;
struct pbuf {struct eth_hdr* payload; } ;
struct ip_addr {scalar_t__ addr; } ;
struct netif {size_t hwaddr_len; int /*<<< orphan*/  (* linkoutput ) (struct netif*,struct pbuf*) ;scalar_t__ hwaddr; struct ip_addr gw; int /*<<< orphan*/  netmask; int /*<<< orphan*/  ip_addr; } ;
struct TYPE_5__ {int* addr; } ;
struct TYPE_4__ {int* addr; } ;
struct eth_hdr {int /*<<< orphan*/  type; TYPE_2__ src; TYPE_1__ dest; } ;
struct eth_addr {int* addr; } ;
typedef  int /*<<< orphan*/  err_t ;
struct TYPE_6__ {int /*<<< orphan*/  lenerr; } ;

/* Variables and functions */
 int DBG_TRACE ; 
 int /*<<< orphan*/  ERR_BUF ; 
 int /*<<< orphan*/  ERR_RTE ; 
 int ETHARP_DEBUG ; 
 int /*<<< orphan*/  ETHTYPE_IP ; 
 int /*<<< orphan*/  LINK_STATS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int,char*) ; 
 int /*<<< orphan*/  etharp_query (struct netif*,struct ip_addr*,struct pbuf*) ; 
 int /*<<< orphan*/  ethbroadcast ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int ip4_addr2 (struct ip_addr*) ; 
 int ip4_addr3 (struct ip_addr*) ; 
 int ip4_addr4 (struct ip_addr*) ; 
 scalar_t__ ip_addr_isbroadcast (struct ip_addr*,struct netif*) ; 
 scalar_t__ ip_addr_ismulticast (struct ip_addr*) ; 
 int /*<<< orphan*/  ip_addr_netcmp (struct ip_addr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__ link ; 
 scalar_t__ pbuf_header (struct pbuf*,int) ; 
 int /*<<< orphan*/  stub1 (struct netif*,struct pbuf*) ; 

err_t
etharp_output(struct netif *netif, struct ip_addr *ipaddr, struct pbuf *q)
{
  struct eth_addr *dest, *srcaddr, mcastaddr;
  struct eth_hdr *ethhdr;
  u8_t i;

  /* make room for Ethernet header - should not fail */
  if (pbuf_header(q, sizeof(struct eth_hdr)) != 0) {
    /* bail out */
    LWIP_DEBUGF(ETHARP_DEBUG | DBG_TRACE | 2, ("etharp_output: could not allocate room for header.\n"));
    LINK_STATS_INC(link.lenerr);
    return ERR_BUF;
  }

  /* assume unresolved Ethernet address */
  dest = NULL;
  /* Determine on destination hardware address. Broadcasts and multicasts
   * are special, other IP addresses are looked up in the ARP table. */

  /* broadcast destination IP address? */
  if (ip_addr_isbroadcast(ipaddr, netif)) {
    /* broadcast on Ethernet also */
    dest = (struct eth_addr *)&ethbroadcast;
  /* multicast destination IP address? */
  } else if (ip_addr_ismulticast(ipaddr)) {
    /* Hash IP multicast address to MAC address.*/
    mcastaddr.addr[0] = 0x01;
    mcastaddr.addr[1] = 0x00;
    mcastaddr.addr[2] = 0x5e;
    mcastaddr.addr[3] = ip4_addr2(ipaddr) & 0x7f;
    mcastaddr.addr[4] = ip4_addr3(ipaddr);
    mcastaddr.addr[5] = ip4_addr4(ipaddr);
    /* destination Ethernet address is multicast */
    dest = &mcastaddr;
  /* unicast destination IP address? */
  } else {
    /* outside local network? */
    if (!ip_addr_netcmp(ipaddr, &(netif->ip_addr), &(netif->netmask))) {
      /* interface has default gateway? */
      if (netif->gw.addr != 0) {
        /* send to hardware address of default gateway IP address */
        ipaddr = &(netif->gw);
      /* no default gateway available */
      } else {
        /* no route to destination error (default gateway missing) */
        return ERR_RTE;
      }
    }
    /* queue on destination Ethernet address belonging to ipaddr */
    return etharp_query(netif, ipaddr, q);
  }

  /* continuation for multicast/broadcast destinations */
  /* obtain source Ethernet address of the given interface */
  srcaddr = (struct eth_addr *)netif->hwaddr;
  ethhdr = q->payload;
  for (i = 0; i < netif->hwaddr_len; i++) {
    ethhdr->dest.addr[i] = dest->addr[i];
    ethhdr->src.addr[i] = srcaddr->addr[i];
  }
  ethhdr->type = htons(ETHTYPE_IP);
  /* send packet directly on the link */
  return netif->linkoutput(netif, q);
}