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
struct pbuf {struct eth_hdr* payload; } ;
struct netif {int /*<<< orphan*/  (* input ) (struct pbuf*,struct netif*) ;struct ethernetif* state; } ;
struct ethernetif {int /*<<< orphan*/  ethaddr; } ;
struct eth_hdr {int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int /*<<< orphan*/  recv; } ;
struct TYPE_4__ {TYPE_1__ link; } ;

/* Variables and functions */
#define  ETHTYPE_ARP 129 
#define  ETHTYPE_IP 128 
 struct pbuf* etharp_arp_input (struct netif*,int /*<<< orphan*/ ,struct pbuf*) ; 
 struct pbuf* etharp_ip_input (struct netif*,struct pbuf*) ; 
 int htons (int /*<<< orphan*/ ) ; 
 struct pbuf* low_level_input (struct ethernetif*) ; 
 int /*<<< orphan*/  low_level_output (struct ethernetif*,struct pbuf*) ; 
 TYPE_2__ lwip_stats ; 
 int /*<<< orphan*/  pbuf_free (struct pbuf*) ; 
 int /*<<< orphan*/  pbuf_header (struct pbuf*,int) ; 
 int /*<<< orphan*/  stub1 (struct pbuf*,struct netif*) ; 

__attribute__((used)) static void
ethernetif_input(struct netif *netif)
{
  struct ethernetif *ethernetif;
  struct eth_hdr *ethhdr;
  struct pbuf *p, *q;

  ethernetif = netif->state;

  p = low_level_input(ethernetif);

  if (p != NULL)
    return;

#ifdef LINK_STATS
  lwip_stats.link.recv++;
#endif /* LINK_STATS */

  ethhdr = p->payload;
  q = NULL;

  switch (htons(ethhdr->type)) {
    case ETHTYPE_IP:
      q = etharp_ip_input(netif, p);
      pbuf_header(p, -14);
      netif->input(p, netif);
      break;

    case ETHTYPE_ARP:
      q = etharp_arp_input(netif, ethernetif->ethaddr, p);
      break;
    default:
      pbuf_free(p);
      p = NULL;
      break;
  }
  if (q != NULL) {
    low_level_output(ethernetif, q);
    pbuf_free(q);
    q = NULL;
  }
}