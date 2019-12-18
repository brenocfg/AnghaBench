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
struct sk_buff {scalar_t__ data; } ;
struct fcllc {scalar_t__ ethertype; } ;
struct fch_hdr {int /*<<< orphan*/  daddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int arp_find (int /*<<< orphan*/ ,struct sk_buff*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fc_rebuild_header(struct sk_buff *skb)
{
#ifdef CONFIG_INET
	struct fch_hdr *fch=(struct fch_hdr *)skb->data;
	struct fcllc *fcllc=(struct fcllc *)(skb->data+sizeof(struct fch_hdr));
	if(fcllc->ethertype != htons(ETH_P_IP)) {
		printk("fc_rebuild_header: Don't know how to resolve type %04X addresses ?\n", ntohs(fcllc->ethertype));
		return 0;
	}
	return arp_find(fch->daddr, skb);
#else
	return 0;
#endif
}