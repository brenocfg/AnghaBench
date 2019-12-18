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
typedef  size_t u16 ;
struct sw_rx_page {struct page* page; } ;
struct page {int dummy; } ;
struct eth_rx_sge {void* addr_lo; void* addr_hi; } ;
struct bnx2x_fastpath {struct eth_rx_sge* rx_sge_ring; struct sw_rx_page* rx_page_ring; } ;
struct bnx2x {TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PAGES_PER_SGE_SHIFT ; 
 int /*<<< orphan*/  SGE_PAGES ; 
 int /*<<< orphan*/  U64_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U64_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __free_pages (struct page*,int /*<<< orphan*/ ) ; 
 struct page* alloc_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_page (int /*<<< orphan*/ *,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_addr_set (struct sw_rx_page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnx2x_alloc_rx_sge(struct bnx2x *bp, struct bnx2x_fastpath *fp,
			      u16 index, gfp_t gfp_mask)
{
	struct page *page = alloc_pages(gfp_mask, PAGES_PER_SGE_SHIFT);
	struct sw_rx_page *sw_buf = &fp->rx_page_ring[index];
	struct eth_rx_sge *sge = &fp->rx_sge_ring[index];
	dma_addr_t mapping;

	if (unlikely(page == NULL)) {
		BNX2X_ERR("Can't alloc sge\n");
		return -ENOMEM;
	}

	mapping = dma_map_page(&bp->pdev->dev, page, 0,
			       SGE_PAGES, DMA_FROM_DEVICE);
	if (unlikely(dma_mapping_error(&bp->pdev->dev, mapping))) {
		__free_pages(page, PAGES_PER_SGE_SHIFT);
		BNX2X_ERR("Can't map sge\n");
		return -ENOMEM;
	}

	sw_buf->page = page;
	dma_unmap_addr_set(sw_buf, mapping, mapping);

	sge->addr_hi = cpu_to_le32(U64_HI(mapping));
	sge->addr_lo = cpu_to_le32(U64_LO(mapping));

	return 0;
}