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
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data; } ;
struct device {int dummy; } ;
struct net_device {int /*<<< orphan*/  trans_start; struct device dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_dropped; } ;
struct emac_priv {TYPE_1__ net_dev_stats; int /*<<< orphan*/  ndev; int /*<<< orphan*/  link; } ;
struct emac_netpktobj {int num_bufs; void* pkt_token; int /*<<< orphan*/  pkt_length; struct emac_netbufobj* buf_list; } ;
struct emac_netbufobj {scalar_t__ data_ptr; void* buf_token; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMAC_CACHE_WRITEBACK (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMAC_DEF_TX_CH ; 
 int EMAC_ERR_TX_OUT_OF_BD ; 
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int emac_send (struct emac_priv*,struct emac_netpktobj*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ net_ratelimit () ; 
 struct emac_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_tx_err (struct emac_priv*) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int emac_dev_xmit(struct sk_buff *skb, struct net_device *ndev)
{
	struct device *emac_dev = &ndev->dev;
	int ret_code;
	struct emac_netbufobj tx_buf; /* buffer obj-only single frame support */
	struct emac_netpktobj tx_packet;  /* packet object */
	struct emac_priv *priv = netdev_priv(ndev);

	/* If no link, return */
	if (unlikely(!priv->link)) {
		if (netif_msg_tx_err(priv) && net_ratelimit())
			dev_err(emac_dev, "DaVinci EMAC: No link to transmit");
		return NETDEV_TX_BUSY;
	}

	/* Build the buffer and packet objects - Since only single fragment is
	 * supported, need not set length and token in both packet & object.
	 * Doing so for completeness sake & to show that this needs to be done
	 * in multifragment case
	 */
	tx_packet.buf_list = &tx_buf;
	tx_packet.num_bufs = 1; /* only single fragment supported */
	tx_packet.pkt_length = skb->len;
	tx_packet.pkt_token = (void *)skb;
	tx_buf.length = skb->len;
	tx_buf.buf_token = (void *)skb;
	tx_buf.data_ptr = skb->data;
	EMAC_CACHE_WRITEBACK((unsigned long)skb->data, skb->len);
	ndev->trans_start = jiffies;
	ret_code = emac_send(priv, &tx_packet, EMAC_DEF_TX_CH);
	if (unlikely(ret_code != 0)) {
		if (ret_code == EMAC_ERR_TX_OUT_OF_BD) {
			if (netif_msg_tx_err(priv) && net_ratelimit())
				dev_err(emac_dev, "DaVinci EMAC: xmit() fatal"\
					" err. Out of TX BD's");
			netif_stop_queue(priv->ndev);
		}
		priv->net_dev_stats.tx_dropped++;
		return NETDEV_TX_BUSY;
	}

	return NETDEV_TX_OK;
}