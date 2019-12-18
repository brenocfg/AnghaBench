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
typedef  int u32 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int len; int /*<<< orphan*/  pa; struct ocrdma_alloc_ucontext_resp* va; } ;
struct ib_ucontext {int dummy; } ;
struct ocrdma_ucontext {TYPE_3__ ah_tbl; struct ib_ucontext ibucontext; int /*<<< orphan*/  mm_list_lock; int /*<<< orphan*/  mm_head; struct ocrdma_dev* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  fw_ver; int /*<<< orphan*/  wqe_size; int /*<<< orphan*/  rqe_size; int /*<<< orphan*/  max_inline_data; } ;
struct TYPE_4__ {struct pci_dev* pdev; } ;
struct ocrdma_dev {TYPE_2__ attr; int /*<<< orphan*/  id; TYPE_1__ nic_info; } ;
struct ocrdma_alloc_ucontext_resp {int ah_tbl_len; int /*<<< orphan*/  fw_ver; int /*<<< orphan*/  dpp_wqe_size; int /*<<< orphan*/  rqe_size; int /*<<< orphan*/  wqe_size; int /*<<< orphan*/  max_inline_data; int /*<<< orphan*/  dev_id; int /*<<< orphan*/  ah_tbl_page; } ;
struct ib_udata {int dummy; } ;
struct ib_device {int dummy; } ;
typedef  int /*<<< orphan*/  resp ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 struct ib_ucontext* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct ocrdma_alloc_ucontext_resp* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,struct ocrdma_alloc_ucontext_resp*,int /*<<< orphan*/ ) ; 
 struct ocrdma_dev* get_ocrdma_dev (struct ib_device*) ; 
 int ib_copy_to_udata (struct ib_udata*,struct ocrdma_alloc_ucontext_resp*,int) ; 
 int /*<<< orphan*/  kfree (struct ocrdma_ucontext*) ; 
 struct ocrdma_ucontext* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct ocrdma_alloc_ucontext_resp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int ocrdma_add_mmap (struct ocrdma_ucontext*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocrdma_del_mmap (struct ocrdma_ucontext*,int /*<<< orphan*/ ,int) ; 
 int roundup (int,int /*<<< orphan*/ ) ; 

struct ib_ucontext *ocrdma_alloc_ucontext(struct ib_device *ibdev,
					  struct ib_udata *udata)
{
	int status;
	struct ocrdma_ucontext *ctx;
	struct ocrdma_alloc_ucontext_resp resp;
	struct ocrdma_dev *dev = get_ocrdma_dev(ibdev);
	struct pci_dev *pdev = dev->nic_info.pdev;
	u32 map_len = roundup(sizeof(u32) * 2048, PAGE_SIZE);

	if (!udata)
		return ERR_PTR(-EFAULT);
	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return ERR_PTR(-ENOMEM);
	ctx->dev = dev;
	INIT_LIST_HEAD(&ctx->mm_head);
	mutex_init(&ctx->mm_list_lock);

	ctx->ah_tbl.va = dma_alloc_coherent(&pdev->dev, map_len,
					    &ctx->ah_tbl.pa, GFP_KERNEL);
	if (!ctx->ah_tbl.va) {
		kfree(ctx);
		return ERR_PTR(-ENOMEM);
	}
	memset(ctx->ah_tbl.va, 0, map_len);
	ctx->ah_tbl.len = map_len;

	memset(&resp, 0, sizeof(resp));
	resp.ah_tbl_len = ctx->ah_tbl.len;
	resp.ah_tbl_page = ctx->ah_tbl.pa;

	status = ocrdma_add_mmap(ctx, resp.ah_tbl_page, resp.ah_tbl_len);
	if (status)
		goto map_err;
	resp.dev_id = dev->id;
	resp.max_inline_data = dev->attr.max_inline_data;
	resp.wqe_size = dev->attr.wqe_size;
	resp.rqe_size = dev->attr.rqe_size;
	resp.dpp_wqe_size = dev->attr.wqe_size;

	memcpy(resp.fw_ver, dev->attr.fw_ver, sizeof(resp.fw_ver));
	status = ib_copy_to_udata(udata, &resp, sizeof(resp));
	if (status)
		goto cpy_err;
	return &ctx->ibucontext;

cpy_err:
	ocrdma_del_mmap(ctx, ctx->ah_tbl.pa, ctx->ah_tbl.len);
map_err:
	dma_free_coherent(&pdev->dev, ctx->ah_tbl.len, ctx->ah_tbl.va,
			  ctx->ah_tbl.pa);
	kfree(ctx);
	return ERR_PTR(status);
}