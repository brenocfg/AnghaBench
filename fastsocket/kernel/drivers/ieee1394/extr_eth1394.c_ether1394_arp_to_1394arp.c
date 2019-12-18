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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {scalar_t__ data; } ;
struct net_device {int dummy; } ;
struct eth1394_priv {int local_fifo; TYPE_2__* host; } ;
struct eth1394_arp {int hw_addr_len; int /*<<< orphan*/  fifo_lo; int /*<<< orphan*/  fifo_hi; int /*<<< orphan*/  sspd; int /*<<< orphan*/  max_rec; int /*<<< orphan*/  sip; } ;
struct arphdr {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  lnk_spd; int /*<<< orphan*/  max_rec; } ;
struct TYPE_4__ {TYPE_1__ csr; } ;

/* Variables and functions */
 int ETH1394_ALEN ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  htons (int) ; 
 struct eth1394_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ether1394_arp_to_1394arp(struct sk_buff *skb,
				     struct net_device *dev)
{
	struct eth1394_priv *priv = netdev_priv(dev);
	struct arphdr *arp = (struct arphdr *)skb->data;
	unsigned char *arp_ptr = (unsigned char *)(arp + 1);
	struct eth1394_arp *arp1394 = (struct eth1394_arp *)skb->data;

	arp1394->hw_addr_len	= 16;
	arp1394->sip		= *(u32*)(arp_ptr + ETH1394_ALEN);
	arp1394->max_rec	= priv->host->csr.max_rec;
	arp1394->sspd		= priv->host->csr.lnk_spd;
	arp1394->fifo_hi	= htons(priv->local_fifo >> 32);
	arp1394->fifo_lo	= htonl(priv->local_fifo & ~0x0);
}