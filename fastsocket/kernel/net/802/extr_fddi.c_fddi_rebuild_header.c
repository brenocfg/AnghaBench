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
struct sk_buff {TYPE_1__* dev; scalar_t__ data; } ;
struct TYPE_5__ {scalar_t__ ethertype; } ;
struct TYPE_6__ {TYPE_2__ llc_snap; } ;
struct fddihdr {TYPE_3__ hdr; int /*<<< orphan*/  daddr; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int arp_find (int /*<<< orphan*/ ,struct sk_buff*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fddi_rebuild_header(struct sk_buff	*skb)
{
	struct fddihdr *fddi = (struct fddihdr *)skb->data;

#ifdef CONFIG_INET
	if (fddi->hdr.llc_snap.ethertype == htons(ETH_P_IP))
		/* Try to get ARP to resolve the header and fill destination address */
		return arp_find(fddi->daddr, skb);
	else
#endif
	{
		printk("%s: Don't know how to resolve type %04X addresses.\n",
		       skb->dev->name, ntohs(fddi->hdr.llc_snap.ethertype));
		return(0);
	}
}