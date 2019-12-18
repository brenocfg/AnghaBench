#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct status_block_msix {int /*<<< orphan*/  status_rx_quick_consumer_index; int /*<<< orphan*/  status_tx_quick_consumer_index; } ;
struct status_block {int dummy; } ;
struct statistics_block {int dummy; } ;
struct TYPE_5__ {struct status_block_msix* msix; TYPE_1__* msi; } ;
struct bnx2_napi {int int_num; int /*<<< orphan*/ * hw_rx_cons_ptr; int /*<<< orphan*/ * hw_tx_cons_ptr; TYPE_2__ status_blk; } ;
struct bnx2 {int flags; int status_stats_size; int irq_nvecs; int ctx_pages; int /*<<< orphan*/ ** ctx_blk; scalar_t__* ctx_blk_mapping; TYPE_3__* pdev; scalar_t__ status_blk_mapping; scalar_t__ stats_blk_mapping; void* stats_blk; struct bnx2_napi* bnx2_napi; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  status_rx_quick_consumer_index0; int /*<<< orphan*/  status_tx_quick_consumer_index0; } ;

/* Variables and functions */
 scalar_t__ BNX2_CHIP (struct bnx2*) ; 
 scalar_t__ BNX2_CHIP_5709 ; 
 int BNX2_FLAG_MSIX_CAP ; 
 int BNX2_MAX_MSIX_HW_VEC ; 
 int BNX2_PAGE_SIZE ; 
 int BNX2_SBLK_MSIX_ALIGN_SIZE ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int L1_CACHE_ALIGN (int) ; 
 int __GFP_ZERO ; 
 int bnx2_alloc_rx_mem (struct bnx2*) ; 
 int bnx2_alloc_tx_mem (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_free_mem (struct bnx2*) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,scalar_t__*,int) ; 

__attribute__((used)) static int
bnx2_alloc_mem(struct bnx2 *bp)
{
	int i, status_blk_size, err;
	struct bnx2_napi *bnapi;
	void *status_blk;

	/* Combine status and statistics blocks into one allocation. */
	status_blk_size = L1_CACHE_ALIGN(sizeof(struct status_block));
	if (bp->flags & BNX2_FLAG_MSIX_CAP)
		status_blk_size = L1_CACHE_ALIGN(BNX2_MAX_MSIX_HW_VEC *
						 BNX2_SBLK_MSIX_ALIGN_SIZE);
	bp->status_stats_size = status_blk_size +
				sizeof(struct statistics_block);

	status_blk = dma_alloc_coherent(&bp->pdev->dev, bp->status_stats_size,
					&bp->status_blk_mapping,
					GFP_KERNEL | __GFP_ZERO);
	if (status_blk == NULL)
		goto alloc_mem_err;

	bnapi = &bp->bnx2_napi[0];
	bnapi->status_blk.msi = status_blk;
	bnapi->hw_tx_cons_ptr =
		&bnapi->status_blk.msi->status_tx_quick_consumer_index0;
	bnapi->hw_rx_cons_ptr =
		&bnapi->status_blk.msi->status_rx_quick_consumer_index0;
	if (bp->flags & BNX2_FLAG_MSIX_CAP) {
		for (i = 1; i < bp->irq_nvecs; i++) {
			struct status_block_msix *sblk;

			bnapi = &bp->bnx2_napi[i];

			sblk = (status_blk + BNX2_SBLK_MSIX_ALIGN_SIZE * i);
			bnapi->status_blk.msix = sblk;
			bnapi->hw_tx_cons_ptr =
				&sblk->status_tx_quick_consumer_index;
			bnapi->hw_rx_cons_ptr =
				&sblk->status_rx_quick_consumer_index;
			bnapi->int_num = i << 24;
		}
	}

	bp->stats_blk = status_blk + status_blk_size;

	bp->stats_blk_mapping = bp->status_blk_mapping + status_blk_size;

	if (BNX2_CHIP(bp) == BNX2_CHIP_5709) {
		bp->ctx_pages = 0x2000 / BNX2_PAGE_SIZE;
		if (bp->ctx_pages == 0)
			bp->ctx_pages = 1;
		for (i = 0; i < bp->ctx_pages; i++) {
			bp->ctx_blk[i] = dma_alloc_coherent(&bp->pdev->dev,
						BNX2_PAGE_SIZE,
						&bp->ctx_blk_mapping[i],
						GFP_KERNEL);
			if (bp->ctx_blk[i] == NULL)
				goto alloc_mem_err;
		}
	}

	err = bnx2_alloc_rx_mem(bp);
	if (err)
		goto alloc_mem_err;

	err = bnx2_alloc_tx_mem(bp);
	if (err)
		goto alloc_mem_err;

	return 0;

alloc_mem_err:
	bnx2_free_mem(bp);
	return -ENOMEM;
}