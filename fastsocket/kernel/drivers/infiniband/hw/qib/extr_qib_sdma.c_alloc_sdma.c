#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct qib_pportdata {int sdma_descq_cnt; scalar_t__ sdma_descq_phys; int /*<<< orphan*/ * sdma_descq; TYPE_2__* dd; scalar_t__* sdma_head_dma; scalar_t__ sdma_head_phys; } ;
struct TYPE_4__ {TYPE_1__* pcidev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,void*,scalar_t__) ; 
 int /*<<< orphan*/  qib_dev_err (TYPE_2__*,char*) ; 
 int sdma_descq_cnt ; 

__attribute__((used)) static int alloc_sdma(struct qib_pportdata *ppd)
{
	ppd->sdma_descq_cnt = sdma_descq_cnt;
	if (!ppd->sdma_descq_cnt)
		ppd->sdma_descq_cnt = 256;

	/* Allocate memory for SendDMA descriptor FIFO */
	ppd->sdma_descq = dma_alloc_coherent(&ppd->dd->pcidev->dev,
		ppd->sdma_descq_cnt * sizeof(u64[2]), &ppd->sdma_descq_phys,
		GFP_KERNEL);

	if (!ppd->sdma_descq) {
		qib_dev_err(ppd->dd,
			"failed to allocate SendDMA descriptor FIFO memory\n");
		goto bail;
	}

	/* Allocate memory for DMA of head register to memory */
	ppd->sdma_head_dma = dma_alloc_coherent(&ppd->dd->pcidev->dev,
		PAGE_SIZE, &ppd->sdma_head_phys, GFP_KERNEL);
	if (!ppd->sdma_head_dma) {
		qib_dev_err(ppd->dd,
			"failed to allocate SendDMA head memory\n");
		goto cleanup_descq;
	}
	ppd->sdma_head_dma[0] = 0;
	return 0;

cleanup_descq:
	dma_free_coherent(&ppd->dd->pcidev->dev,
		ppd->sdma_descq_cnt * sizeof(u64[2]), (void *)ppd->sdma_descq,
		ppd->sdma_descq_phys);
	ppd->sdma_descq = NULL;
	ppd->sdma_descq_phys = 0;
bail:
	ppd->sdma_descq_cnt = 0;
	return -ENOMEM;
}