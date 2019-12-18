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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct skb_shared_hwtstamps {int dummy; } ;
struct skb_frag_struct {int /*<<< orphan*/  size; } ;
struct sk_buff {int dummy; } ;
struct mlx4_wqe_data_seg {int /*<<< orphan*/  addr; int /*<<< orphan*/  byte_count; } ;
struct mlx4_en_tx_ring {int buf_size; struct mlx4_en_tx_desc* buf; struct mlx4_en_tx_info* tx_info; } ;
struct mlx4_en_tx_info {int data_offset; int nr_txbb; scalar_t__ linear; int /*<<< orphan*/  inl; struct sk_buff* skb; } ;
struct mlx4_en_tx_desc {int dummy; } ;
struct mlx4_en_priv {int /*<<< orphan*/  ddev; struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int nr_frags; struct skb_frag_struct* frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int TXBB_SIZE ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mlx4_en_fill_hwtstamps (struct mlx4_en_dev*,struct skb_shared_hwtstamps*,int /*<<< orphan*/ ) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_tstamp_tx (struct sk_buff*,struct skb_shared_hwtstamps*) ; 

__attribute__((used)) static u32 mlx4_en_free_tx_desc(struct mlx4_en_priv *priv,
				struct mlx4_en_tx_ring *ring,
				int index, u8 owner, u64 timestamp)
{
	struct mlx4_en_dev *mdev = priv->mdev;
	struct mlx4_en_tx_info *tx_info = &ring->tx_info[index];
	struct mlx4_en_tx_desc *tx_desc = ring->buf + index * TXBB_SIZE;
	struct mlx4_wqe_data_seg *data = (void *) tx_desc + tx_info->data_offset;
	struct sk_buff *skb = tx_info->skb;
	struct skb_frag_struct *frag;
	void *end = ring->buf + ring->buf_size;
	int frags = skb_shinfo(skb)->nr_frags;
	int i;
	struct skb_shared_hwtstamps hwts;

	if (timestamp) {
		mlx4_en_fill_hwtstamps(mdev, &hwts, timestamp);
		skb_tstamp_tx(skb, &hwts);
	}

	/* Optimize the common case when there are no wraparounds */
	if (likely((void *) tx_desc + tx_info->nr_txbb * TXBB_SIZE <= end)) {
		if (!tx_info->inl) {
			if (tx_info->linear) {
				dma_unmap_single(priv->ddev,
					(dma_addr_t) be64_to_cpu(data->addr),
					 be32_to_cpu(data->byte_count),
					 PCI_DMA_TODEVICE);
				++data;
			}

			for (i = 0; i < frags; i++) {
				frag = &skb_shinfo(skb)->frags[i];
				dma_unmap_page(priv->ddev,
					(dma_addr_t) be64_to_cpu(data[i].addr),
					frag->size, PCI_DMA_TODEVICE);
			}
		}
	} else {
		if (!tx_info->inl) {
			if ((void *) data >= end) {
				data = (struct mlx4_wqe_data_seg *)
						(ring->buf + ((void *) data - end));
			}

			if (tx_info->linear) {
				dma_unmap_single(priv->ddev,
					(dma_addr_t) be64_to_cpu(data->addr),
					 be32_to_cpu(data->byte_count),
					 PCI_DMA_TODEVICE);
				++data;
			}

			for (i = 0; i < frags; i++) {
				/* Check for wraparound before unmapping */
				if ((void *) data >= end)
					data = (struct mlx4_wqe_data_seg *) ring->buf;
				frag = &skb_shinfo(skb)->frags[i];
				dma_unmap_page(priv->ddev,
					(dma_addr_t) be64_to_cpu(data->addr),
					 frag->size, PCI_DMA_TODEVICE);
				++data;
			}
		}
	}
	dev_kfree_skb_any(skb);
	return tx_info->nr_txbb;
}