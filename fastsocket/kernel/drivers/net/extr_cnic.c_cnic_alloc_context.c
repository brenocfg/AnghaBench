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
typedef  int u32 ;
struct cnic_local {int ctx_blk_size; int cids_per_blk; int ctx_blks; TYPE_2__* ctx_arr; } ;
struct cnic_dev {TYPE_1__* pcidev; struct cnic_local* cnic_priv; } ;
struct cnic_ctx {int dummy; } ;
struct TYPE_4__ {int cid; int /*<<< orphan*/ * ctx; int /*<<< orphan*/  mapping; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BNX2_CHIP (struct cnic_local*) ; 
 scalar_t__ BNX2_CHIP_5709 ; 
 int BNX2_ISCSI_CTX_MAP ; 
 int BNX2_MAX_CID ; 
 int BNX2_PAGE_SIZE ; 
 int BNX2_PG_CTX_MAP ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int cnic_reg_rd_ind (struct cnic_dev*,int) ; 
 int /*<<< orphan*/ * dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cnic_alloc_context(struct cnic_dev *dev)
{
	struct cnic_local *cp = dev->cnic_priv;

	if (BNX2_CHIP(cp) == BNX2_CHIP_5709) {
		int i, k, arr_size;

		cp->ctx_blk_size = BNX2_PAGE_SIZE;
		cp->cids_per_blk = BNX2_PAGE_SIZE / 128;
		arr_size = BNX2_MAX_CID / cp->cids_per_blk *
			   sizeof(struct cnic_ctx);
		cp->ctx_arr = kzalloc(arr_size, GFP_KERNEL);
		if (cp->ctx_arr == NULL)
			return -ENOMEM;

		k = 0;
		for (i = 0; i < 2; i++) {
			u32 j, reg, off, lo, hi;

			if (i == 0)
				off = BNX2_PG_CTX_MAP;
			else
				off = BNX2_ISCSI_CTX_MAP;

			reg = cnic_reg_rd_ind(dev, off);
			lo = reg >> 16;
			hi = reg & 0xffff;
			for (j = lo; j < hi; j += cp->cids_per_blk, k++)
				cp->ctx_arr[k].cid = j;
		}

		cp->ctx_blks = k;
		if (cp->ctx_blks >= (BNX2_MAX_CID / cp->cids_per_blk)) {
			cp->ctx_blks = 0;
			return -ENOMEM;
		}

		for (i = 0; i < cp->ctx_blks; i++) {
			cp->ctx_arr[i].ctx =
				dma_alloc_coherent(&dev->pcidev->dev,
						   BNX2_PAGE_SIZE,
						   &cp->ctx_arr[i].mapping,
						   GFP_KERNEL);
			if (cp->ctx_arr[i].ctx == NULL)
				return -ENOMEM;
		}
	}
	return 0;
}