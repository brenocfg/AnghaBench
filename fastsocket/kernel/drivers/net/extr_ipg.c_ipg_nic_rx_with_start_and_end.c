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
struct sk_buff {int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  protocol; } ;
struct net_device {int dummy; } ;
struct ipg_rx {int /*<<< orphan*/  rfs; } ;
struct ipg_jumbo {int /*<<< orphan*/ * skb; scalar_t__ current_size; scalar_t__ found_start; } ;
struct ipg_nic_private {int rxfrag_size; struct sk_buff** rx_buff; struct ipg_jumbo jumbo; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int IPG_RFS_RXFRAMELEN ; 
 scalar_t__ NORMAL_PACKET ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 scalar_t__ ipg_nic_rx_check_error (struct net_device*) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static void ipg_nic_rx_with_start_and_end(struct net_device *dev,
					  struct ipg_nic_private *sp,
					  struct ipg_rx *rxfd, unsigned entry)
{
	struct ipg_jumbo *jumbo = &sp->jumbo;
	struct sk_buff *skb;
	int framelen;

	if (jumbo->found_start) {
		dev_kfree_skb_irq(jumbo->skb);
		jumbo->found_start = 0;
		jumbo->current_size = 0;
		jumbo->skb = NULL;
	}

	/* 1: found error, 0 no error */
	if (ipg_nic_rx_check_error(dev) != NORMAL_PACKET)
		return;

	skb = sp->rx_buff[entry];
	if (!skb)
		return;

	/* accept this frame and send to upper layer */
	framelen = le64_to_cpu(rxfd->rfs) & IPG_RFS_RXFRAMELEN;
	if (framelen > sp->rxfrag_size)
		framelen = sp->rxfrag_size;

	skb_put(skb, framelen);
	skb->protocol = eth_type_trans(skb, dev);
	skb->ip_summed = CHECKSUM_NONE;
	netif_rx(skb);
	sp->rx_buff[entry] = NULL;
}