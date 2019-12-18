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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {void* data; struct net_device* dev; } ;
struct device {int dummy; } ;
struct net_device {struct device dev; } ;
struct emac_priv {struct net_device* ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMAC_CACHE_WRITEBACK_INVALIDATE (unsigned long,int) ; 
 int /*<<< orphan*/  NET_IP_ALIGN ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ net_ratelimit () ; 
 scalar_t__ netif_msg_rx_err (struct emac_priv*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void *emac_net_alloc_rx_buf(struct emac_priv *priv, int buf_size,
		void **data_token, u32 ch)
{
	struct net_device *ndev = priv->ndev;
	struct device *emac_dev = &ndev->dev;
	struct sk_buff *p_skb;

	p_skb = dev_alloc_skb(buf_size);
	if (unlikely(NULL == p_skb)) {
		if (netif_msg_rx_err(priv) && net_ratelimit())
			dev_err(emac_dev, "DaVinci EMAC: failed to alloc skb");
		return NULL;
	}

	/* set device pointer in skb and reserve space for extra bytes */
	p_skb->dev = ndev;
	skb_reserve(p_skb, NET_IP_ALIGN);
	*data_token = (void *) p_skb;
	EMAC_CACHE_WRITEBACK_INVALIDATE((unsigned long)p_skb->data, buf_size);
	return p_skb->data;
}