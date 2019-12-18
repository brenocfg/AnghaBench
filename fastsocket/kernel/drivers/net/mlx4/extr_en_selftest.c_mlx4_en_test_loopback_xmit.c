#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct mlx4_en_priv {TYPE_1__* dev; } ;
struct ethhdr {int /*<<< orphan*/  h_proto; int /*<<< orphan*/  h_source; int /*<<< orphan*/  h_dest; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_ARP ; 
 unsigned int MLX4_LOOPBACK_TEST_PAYLOAD ; 
 scalar_t__ NET_IP_ALIGN ; 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx4_en_xmit (struct sk_buff*,TYPE_1__*) ; 
 struct sk_buff* netdev_alloc_skb (TYPE_1__*,scalar_t__) ; 
 scalar_t__ skb_put (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_set_mac_header (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx4_en_test_loopback_xmit(struct mlx4_en_priv *priv)
{
	struct sk_buff *skb;
	struct ethhdr *ethh;
	unsigned char *packet;
	unsigned int packet_size = MLX4_LOOPBACK_TEST_PAYLOAD;
	unsigned int i;
	int err;


	/* build the pkt before xmit */
	skb = netdev_alloc_skb(priv->dev, MLX4_LOOPBACK_TEST_PAYLOAD + ETH_HLEN + NET_IP_ALIGN);
	if (!skb) {
		en_err(priv, "-LOOPBACK_TEST_XMIT- failed to create skb for xmit\n");
		return -ENOMEM;
	}
	skb_reserve(skb, NET_IP_ALIGN);

	ethh = (struct ethhdr *)skb_put(skb, sizeof(struct ethhdr));
	packet	= (unsigned char *)skb_put(skb, packet_size);
	memcpy(ethh->h_dest, priv->dev->dev_addr, ETH_ALEN);
	memset(ethh->h_source, 0, ETH_ALEN);
	ethh->h_proto = htons(ETH_P_ARP);
	skb_set_mac_header(skb, 0);
	for (i = 0; i < packet_size; ++i)	/* fill our packet */
		packet[i] = (unsigned char)(i & 0xff);

	/* xmit the pkt */
	err = mlx4_en_xmit(skb, priv->dev);
	return err;
}