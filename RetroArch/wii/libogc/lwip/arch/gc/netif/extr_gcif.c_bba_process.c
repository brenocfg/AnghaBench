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
struct pbuf {struct eth_hdr* payload; } ;
struct netif {scalar_t__ state; } ;
struct eth_hdr {int /*<<< orphan*/  type; } ;
struct bba_priv {int /*<<< orphan*/  ethaddr; } ;
typedef  int s32 ;

/* Variables and functions */
#define  ETHTYPE_ARP 129 
#define  ETHTYPE_IP 128 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NETIF_DEBUG ; 
 int /*<<< orphan*/  etharp_arp_input (struct netif*,int /*<<< orphan*/ ,struct pbuf*) ; 
 int /*<<< orphan*/  etharp_ip_input (struct netif*,struct pbuf*) ; 
 int htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_input (struct pbuf*,struct netif*) ; 
 int /*<<< orphan*/  pbuf_free (struct pbuf*) ; 
 int /*<<< orphan*/  pbuf_header (struct pbuf*,int const) ; 

void bba_process(struct pbuf *p,struct netif *dev)
{
	struct eth_hdr *ethhdr = NULL;
	struct bba_priv *priv = (struct bba_priv*)dev->state;
	const s32 hlen = sizeof(struct eth_hdr);

	if(p) {
		ethhdr = p->payload;
		switch(htons(ethhdr->type)) {
			case ETHTYPE_IP:
				LWIP_DEBUGF(NETIF_DEBUG,("bba_process: passing packet up to IP layer\n"));

				etharp_ip_input(dev,p);
				pbuf_header(p,-(hlen));
				ip_input(p,dev);
				break;
			case ETHTYPE_ARP:
				/* pass p to ARP module, get ARP reply or ARP queued packet */
				LWIP_DEBUGF(NETIF_DEBUG,("bba_process: passing packet up to ARP layer\n"));
				etharp_arp_input(dev, priv->ethaddr, p);
				break;
			/* unsupported Ethernet packet type */
			default:
				/* free pbuf */
				pbuf_free(p);
				break;
		}
	}
}