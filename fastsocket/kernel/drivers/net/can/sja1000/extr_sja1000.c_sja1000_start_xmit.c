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
typedef  int uint8_t ;
struct sk_buff {scalar_t__ data; } ;
struct sja1000_priv {int /*<<< orphan*/  (* write_reg ) (struct sja1000_priv*,int /*<<< orphan*/ ,int) ;} ;
struct net_device {int /*<<< orphan*/  trans_start; } ;
struct can_frame {int can_dlc; int can_id; int* data; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
typedef  int canid_t ;

/* Variables and functions */
 int CAN_EFF_FLAG ; 
 int CAN_RTR_FLAG ; 
 int CMD_TR ; 
 int EFF_BUF ; 
 int FI_FF ; 
 int FI_RTR ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  REG_CMR ; 
 int /*<<< orphan*/  REG_FI ; 
 int /*<<< orphan*/  REG_ID1 ; 
 int /*<<< orphan*/  REG_ID2 ; 
 int /*<<< orphan*/  REG_ID3 ; 
 int /*<<< orphan*/  REG_ID4 ; 
 int SFF_BUF ; 
 int /*<<< orphan*/  can_put_echo_skb (struct sk_buff*,struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 struct sja1000_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct sja1000_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub10 (struct sja1000_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct sja1000_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct sja1000_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct sja1000_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (struct sja1000_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub6 (struct sja1000_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub7 (struct sja1000_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub8 (struct sja1000_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub9 (struct sja1000_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static netdev_tx_t sja1000_start_xmit(struct sk_buff *skb,
					    struct net_device *dev)
{
	struct sja1000_priv *priv = netdev_priv(dev);
	struct can_frame *cf = (struct can_frame *)skb->data;
	uint8_t fi;
	uint8_t dlc;
	canid_t id;
	uint8_t dreg;
	int i;

	netif_stop_queue(dev);

	fi = dlc = cf->can_dlc;
	id = cf->can_id;

	if (id & CAN_RTR_FLAG)
		fi |= FI_RTR;

	if (id & CAN_EFF_FLAG) {
		fi |= FI_FF;
		dreg = EFF_BUF;
		priv->write_reg(priv, REG_FI, fi);
		priv->write_reg(priv, REG_ID1, (id & 0x1fe00000) >> (5 + 16));
		priv->write_reg(priv, REG_ID2, (id & 0x001fe000) >> (5 + 8));
		priv->write_reg(priv, REG_ID3, (id & 0x00001fe0) >> 5);
		priv->write_reg(priv, REG_ID4, (id & 0x0000001f) << 3);
	} else {
		dreg = SFF_BUF;
		priv->write_reg(priv, REG_FI, fi);
		priv->write_reg(priv, REG_ID1, (id & 0x000007f8) >> 3);
		priv->write_reg(priv, REG_ID2, (id & 0x00000007) << 5);
	}

	for (i = 0; i < dlc; i++)
		priv->write_reg(priv, dreg++, cf->data[i]);

	dev->trans_start = jiffies;

	can_put_echo_skb(skb, dev, 0);

	priv->write_reg(priv, REG_CMR, CMD_TR);

	return NETDEV_TX_OK;
}