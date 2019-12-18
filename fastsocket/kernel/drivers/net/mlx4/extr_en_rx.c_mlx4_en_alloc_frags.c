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
struct page {int /*<<< orphan*/  _count; } ;
struct mlx4_en_rx_desc {TYPE_1__* data; } ;
struct mlx4_en_rx_alloc {scalar_t__ offset; scalar_t__ size; scalar_t__ dma; scalar_t__ page; } ;
struct mlx4_en_priv {int num_frags; int /*<<< orphan*/  ddev; struct mlx4_en_frag_info* frag_info; } ;
struct mlx4_en_frag_info {scalar_t__ frag_stride; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MLX4_EN_MAX_RX_FRAGS ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cpu_to_be64 (scalar_t__) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx4_alloc_pages (struct mlx4_en_priv*,struct mlx4_en_rx_alloc*,struct mlx4_en_frag_info const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

__attribute__((used)) static int mlx4_en_alloc_frags(struct mlx4_en_priv *priv,
			       struct mlx4_en_rx_desc *rx_desc,
			       struct mlx4_en_rx_alloc *frags,
			       struct mlx4_en_rx_alloc *ring_alloc,
			       gfp_t gfp)
{
	struct mlx4_en_rx_alloc page_alloc[MLX4_EN_MAX_RX_FRAGS];
	const struct mlx4_en_frag_info *frag_info;
	struct page *page;
	dma_addr_t dma;
	int i;

	for (i = 0; i < priv->num_frags; i++) {
		frag_info = &priv->frag_info[i];
		page_alloc[i] = ring_alloc[i];
		page_alloc[i].offset += frag_info->frag_stride;
		if (page_alloc[i].offset + frag_info->frag_stride <= ring_alloc[i].size)
			continue;
		if (mlx4_alloc_pages(priv, &page_alloc[i], frag_info, gfp))
			goto out;
	}

	for (i = 0; i < priv->num_frags; i++) {
		frags[i] = ring_alloc[i];
		dma = ring_alloc[i].dma + ring_alloc[i].offset;
		ring_alloc[i] = page_alloc[i];
		rx_desc->data[i].addr = cpu_to_be64(dma);
	}

	return 0;

out:
	while (i--) {
		frag_info = &priv->frag_info[i];
		if (page_alloc[i].page != ring_alloc[i].page) {
			dma_unmap_page(priv->ddev, page_alloc[i].dma,
				page_alloc[i].size, PCI_DMA_FROMDEVICE);
			page = page_alloc[i].page;
			atomic_set(&page->_count, 1);
			put_page(page);
		}
	}
	return -ENOMEM;
}