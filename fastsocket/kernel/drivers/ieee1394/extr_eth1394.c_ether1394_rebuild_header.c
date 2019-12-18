#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {TYPE_1__* dev; scalar_t__ data; } ;
struct eth1394hdr {scalar_t__ h_proto; int /*<<< orphan*/  h_dest; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH1394_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int arp_find (unsigned char*,struct sk_buff*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (scalar_t__) ; 

__attribute__((used)) static int ether1394_rebuild_header(struct sk_buff *skb)
{
	struct eth1394hdr *eth = (struct eth1394hdr *)skb->data;

	if (eth->h_proto == htons(ETH_P_IP))
		return arp_find((unsigned char *)&eth->h_dest, skb);

	ETH1394_PRINT(KERN_DEBUG, skb->dev->name,
		      "unable to resolve type %04x addresses\n",
		      ntohs(eth->h_proto));
	return 0;
}