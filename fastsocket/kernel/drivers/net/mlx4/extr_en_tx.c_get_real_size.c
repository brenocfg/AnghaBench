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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct mlx4_en_priv {int dummy; } ;
struct TYPE_2__ {int nr_frags; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int CTRL_SIZE ; 
 int DS_SIZE ; 
 int /*<<< orphan*/  en_warn (struct mlx4_en_priv*,char*) ; 
 int inline_size (struct sk_buff*) ; 
 int /*<<< orphan*/  is_inline (struct sk_buff*,int /*<<< orphan*/ *) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_tx_err (struct mlx4_en_priv*) ; 
 int skb_headlen (struct sk_buff*) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int skb_transport_offset (struct sk_buff*) ; 
 int tcp_hdrlen (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int get_real_size(struct sk_buff *skb, struct net_device *dev,
			 int *lso_header_size)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	int real_size;

	if (skb_is_gso(skb)) {
		*lso_header_size = skb_transport_offset(skb) + tcp_hdrlen(skb);
		real_size = CTRL_SIZE + skb_shinfo(skb)->nr_frags * DS_SIZE +
			ALIGN(*lso_header_size + 4, DS_SIZE);
		if (unlikely(*lso_header_size != skb_headlen(skb))) {
			/* We add a segment for the skb linear buffer only if
			 * it contains data */
			if (*lso_header_size < skb_headlen(skb))
				real_size += DS_SIZE;
			else {
				if (netif_msg_tx_err(priv))
					en_warn(priv, "Non-linear headers\n");
				return 0;
			}
		}
	} else {
		*lso_header_size = 0;
		if (!is_inline(skb, NULL))
			real_size = CTRL_SIZE + (skb_shinfo(skb)->nr_frags + 1) * DS_SIZE;
		else
			real_size = inline_size(skb);
	}

	return real_size;
}