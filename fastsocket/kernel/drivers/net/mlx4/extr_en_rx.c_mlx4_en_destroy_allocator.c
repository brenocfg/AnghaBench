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
struct mlx4_en_rx_ring {struct mlx4_en_rx_alloc* page_alloc; } ;
struct mlx4_en_rx_alloc {scalar_t__ size; scalar_t__ offset; int /*<<< orphan*/ * page; int /*<<< orphan*/  dma; } ;
struct mlx4_en_priv {int num_frags; int /*<<< orphan*/  ddev; struct mlx4_en_frag_info* frag_info; } ;
struct mlx4_en_frag_info {scalar_t__ frag_stride; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  en_dbg (int /*<<< orphan*/ ,struct mlx4_en_priv*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx4_en_destroy_allocator(struct mlx4_en_priv *priv,
				      struct mlx4_en_rx_ring *ring)
{
	struct mlx4_en_rx_alloc *page_alloc;
	int i;

	for (i = 0; i < priv->num_frags; i++) {
		const struct mlx4_en_frag_info *frag_info = &priv->frag_info[i];

		page_alloc = &ring->page_alloc[i];
		en_dbg(DRV, priv, "Freeing allocator:%d count:%d\n",
		       i, page_count(page_alloc->page));

		dma_unmap_page(priv->ddev, page_alloc->dma,
				page_alloc->size, PCI_DMA_FROMDEVICE);
		while (page_alloc->offset + frag_info->frag_stride < page_alloc->size) {
			put_page(page_alloc->page);
			page_alloc->offset += frag_info->frag_stride;
		}
		page_alloc->page = NULL;
	}
}