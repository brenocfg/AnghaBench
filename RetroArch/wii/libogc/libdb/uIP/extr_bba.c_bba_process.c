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
struct uip_pbuf {struct uip_eth_hdr* payload; } ;
struct uip_netif {int /*<<< orphan*/  (* input ) (struct uip_pbuf*,struct uip_netif*) ;scalar_t__ state; } ;
struct uip_eth_hdr {int /*<<< orphan*/  type; } ;
struct bba_priv {int /*<<< orphan*/  ethaddr; } ;
typedef  int s32 ;

/* Variables and functions */
#define  UIP_ETHTYPE_ARP 129 
#define  UIP_ETHTYPE_IP 128 
 int htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct uip_pbuf*,struct uip_netif*) ; 
 int /*<<< orphan*/  uip_arp_arpin (struct uip_netif*,int /*<<< orphan*/ ,struct uip_pbuf*) ; 
 int /*<<< orphan*/  uip_arp_ipin (struct uip_netif*,struct uip_pbuf*) ; 
 int /*<<< orphan*/  uip_pbuf_free (struct uip_pbuf*) ; 
 int /*<<< orphan*/  uip_pbuf_header (struct uip_pbuf*,int const) ; 

__attribute__((used)) static void bba_process(struct uip_pbuf *p,struct uip_netif *dev)
{
	struct uip_eth_hdr *ethhdr = NULL;
	struct bba_priv *priv = (struct bba_priv*)dev->state;
	const s32 ethhlen = sizeof(struct uip_eth_hdr);

	if(p) {
		ethhdr = p->payload;
		switch(htons(ethhdr->type)) {
			case UIP_ETHTYPE_IP:
				uip_arp_ipin(dev,p);
				uip_pbuf_header(p,-(ethhlen));
				dev->input(p,dev);
				break;
			case UIP_ETHTYPE_ARP:
				uip_arp_arpin(dev,priv->ethaddr,p);
				break;
			default:
				uip_pbuf_free(p);
				break;
		}
	}
}