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
struct bcm_enet_priv {int hw_mtu; int /*<<< orphan*/  rx_skb_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (scalar_t__,int) ; 
 int BCMENET_DMA_MAXBURST ; 
 int BCMENET_MAX_MTU ; 
 int EINVAL ; 
 scalar_t__ ETH_FCS_LEN ; 
 scalar_t__ VLAN_ETH_HLEN ; 

__attribute__((used)) static int compute_hw_mtu(struct bcm_enet_priv *priv, int mtu)
{
	int actual_mtu;

	actual_mtu = mtu;

	/* add ethernet header + vlan tag size */
	actual_mtu += VLAN_ETH_HLEN;

	if (actual_mtu < 64 || actual_mtu > BCMENET_MAX_MTU)
		return -EINVAL;

	/*
	 * setup maximum size before we get overflow mark in
	 * descriptor, note that this will not prevent reception of
	 * big frames, they will be split into multiple buffers
	 * anyway
	 */
	priv->hw_mtu = actual_mtu;

	/*
	 * align rx buffer size to dma burst len, account FCS since
	 * it's appended
	 */
	priv->rx_skb_size = ALIGN(actual_mtu + ETH_FCS_LEN,
				  BCMENET_DMA_MAXBURST * 4);
	return 0;
}