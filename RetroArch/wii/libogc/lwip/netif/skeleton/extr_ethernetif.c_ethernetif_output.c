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
typedef  int /*<<< orphan*/  u8_t ;
struct pbuf {int dummy; } ;
struct netif {struct ethernetif* state; } ;
struct ip_addr {int dummy; } ;
struct ethernetif {int dummy; } ;
struct eth_hdr {int dummy; } ;
struct eth_addr {int dummy; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_OK ; 
 struct pbuf* etharp_output (struct netif*,struct ip_addr*,struct pbuf*) ; 
 int /*<<< orphan*/  low_level_output (struct ethernetif*,struct pbuf*) ; 

__attribute__((used)) static err_t
ethernetif_output(struct netif *netif, struct pbuf *p,
      struct ip_addr *ipaddr)
{
  struct ethernetif *ethernetif;
  struct pbuf *q;
  struct eth_hdr *ethhdr;
  struct eth_addr *dest, mcastaddr;
  struct ip_addr *queryaddr;
  err_t err;
  u8_t i;

  ethernetif = netif->state;

  /* resolve the link destination hardware address */
  p = etharp_output(netif, ipaddr, p);

  /* network hardware address obtained? */
  if (p == NULL)
  {
    /* we cannot tell if the packet was sent: the packet could */
    /* have been queued on an ARP entry that was already pending. */
  	return ERR_OK;
  }

  /* send out the packet */
  return low_level_output(ethernetif, p);

}