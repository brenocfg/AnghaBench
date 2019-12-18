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
struct net_device {int mtu; } ;
struct mlx4_en_rx_alloc {int dummy; } ;
struct mlx4_en_priv {int num_frags; int rx_skb_size; TYPE_1__* frag_info; int /*<<< orphan*/  log_rx_info; } ;
struct TYPE_2__ {int frag_size; int frag_prefix_size; int frag_align; void* frag_stride; } ;

/* Variables and functions */
 void* ALIGN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRV ; 
 int ETH_HLEN ; 
 int ETH_LLC_SNAP_SIZE ; 
 int NET_IP_ALIGN ; 
 int /*<<< orphan*/  ROUNDUP_LOG2 (int) ; 
 int /*<<< orphan*/  SMP_CACHE_BYTES ; 
 int VLAN_HLEN ; 
 int /*<<< orphan*/  en_dbg (int /*<<< orphan*/ ,struct mlx4_en_priv*,char*,int,int) ; 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*,int,int,int,int,void*) ; 
 int* frag_sizes ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

void mlx4_en_calc_rx_buf(struct net_device *dev)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	int eff_mtu = dev->mtu + ETH_HLEN + VLAN_HLEN + ETH_LLC_SNAP_SIZE;
	int buf_size = 0;
	int i = 0;

	while (buf_size < eff_mtu) {
		priv->frag_info[i].frag_size =
			(eff_mtu > buf_size + frag_sizes[i]) ?
				frag_sizes[i] : eff_mtu - buf_size;
		priv->frag_info[i].frag_prefix_size = buf_size;
		if (!i)	{
			priv->frag_info[i].frag_align = NET_IP_ALIGN;
			priv->frag_info[i].frag_stride =
				ALIGN(frag_sizes[i] + NET_IP_ALIGN, SMP_CACHE_BYTES);
		} else {
			priv->frag_info[i].frag_align = 0;
			priv->frag_info[i].frag_stride =
				ALIGN(frag_sizes[i], SMP_CACHE_BYTES);
		}
		buf_size += priv->frag_info[i].frag_size;
		i++;
	}

	priv->num_frags = i;
	priv->rx_skb_size = eff_mtu;
	priv->log_rx_info = ROUNDUP_LOG2(i * sizeof(struct mlx4_en_rx_alloc));

	en_dbg(DRV, priv, "Rx buffer scatter-list (effective-mtu:%d "
		  "num_frags:%d):\n", eff_mtu, priv->num_frags);
	for (i = 0; i < priv->num_frags; i++) {
		en_err(priv,
		       "  frag:%d - size:%d prefix:%d align:%d stride:%d\n",
		       i,
		       priv->frag_info[i].frag_size,
		       priv->frag_info[i].frag_prefix_size,
		       priv->frag_info[i].frag_align,
		       priv->frag_info[i].frag_stride);
	}
}