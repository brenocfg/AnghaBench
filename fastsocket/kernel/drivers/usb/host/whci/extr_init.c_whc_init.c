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
typedef  int /*<<< orphan*/  u32 ;
struct whc_qset {int dummy; } ;
struct whc {int n_devices; void* di_buf; int /*<<< orphan*/  di_buf_dma; TYPE_2__* umc; void* dn_buf; int /*<<< orphan*/  dn_buf_dma; int /*<<< orphan*/ * gen_cmd_buf; int /*<<< orphan*/  gen_cmd_buf_dma; int /*<<< orphan*/ * qset_pool; int /*<<< orphan*/  n_mmc_ies; int /*<<< orphan*/  n_keys; scalar_t__ base; scalar_t__ base_phys; int /*<<< orphan*/  periodic_removed_list; int /*<<< orphan*/ * periodic_list; int /*<<< orphan*/  periodic_work; int /*<<< orphan*/  async_removed_list; int /*<<< orphan*/  async_list; int /*<<< orphan*/  async_work; int /*<<< orphan*/  dn_work; int /*<<< orphan*/ * workqueue; int /*<<< orphan*/  periodic_list_wq; int /*<<< orphan*/  async_list_wq; int /*<<< orphan*/  cmd_wq; int /*<<< orphan*/  mutex; int /*<<< orphan*/  lock; } ;
struct dn_buf_entry {int dummy; } ;
struct di_buf_entry {int dummy; } ;
typedef  scalar_t__ resource_size_t ;
struct TYPE_3__ {scalar_t__ end; scalar_t__ start; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; TYPE_1__ resource; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ WHCSPARAMS ; 
 int WHCSPARAMS_TO_N_DEVICES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WHCSPARAMS_TO_N_KEYS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WHCSPARAMS_TO_N_MMC_IES (int /*<<< orphan*/ ) ; 
 int WHC_GEN_CMD_DATA_LEN ; 
 int WHC_N_DN_ENTRIES ; 
 int asl_init (struct whc*) ; 
 int /*<<< orphan*/ * create_singlethread_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dma_pool_create (char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 scalar_t__ ioremap (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  le_readl (scalar_t__) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int pzl_init (struct whc*) ; 
 int /*<<< orphan*/  request_mem_region (scalar_t__,scalar_t__,char*) ; 
 int /*<<< orphan*/  scan_async_work ; 
 int /*<<< orphan*/  scan_periodic_work ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  whc_clean_up (struct whc*) ; 
 int /*<<< orphan*/  whc_dn_work ; 
 int /*<<< orphan*/  whc_hw_init_di_buf (struct whc*) ; 
 int /*<<< orphan*/  whc_hw_init_dn_buf (struct whc*) ; 
 int /*<<< orphan*/  whc_hw_reset (struct whc*) ; 

int whc_init(struct whc *whc)
{
	u32 whcsparams;
	int ret, i;
	resource_size_t start, len;

	spin_lock_init(&whc->lock);
	mutex_init(&whc->mutex);
	init_waitqueue_head(&whc->cmd_wq);
	init_waitqueue_head(&whc->async_list_wq);
	init_waitqueue_head(&whc->periodic_list_wq);
	whc->workqueue = create_singlethread_workqueue(dev_name(&whc->umc->dev));
	if (whc->workqueue == NULL) {
		ret = -ENOMEM;
		goto error;
	}
	INIT_WORK(&whc->dn_work, whc_dn_work);

	INIT_WORK(&whc->async_work, scan_async_work);
	INIT_LIST_HEAD(&whc->async_list);
	INIT_LIST_HEAD(&whc->async_removed_list);

	INIT_WORK(&whc->periodic_work, scan_periodic_work);
	for (i = 0; i < 5; i++)
		INIT_LIST_HEAD(&whc->periodic_list[i]);
	INIT_LIST_HEAD(&whc->periodic_removed_list);

	/* Map HC registers. */
	start = whc->umc->resource.start;
	len   = whc->umc->resource.end - start + 1;
	if (!request_mem_region(start, len, "whci-hc")) {
		dev_err(&whc->umc->dev, "can't request HC region\n");
		ret = -EBUSY;
		goto error;
	}
	whc->base_phys = start;
	whc->base = ioremap(start, len);
	if (!whc->base) {
		dev_err(&whc->umc->dev, "ioremap\n");
		ret = -ENOMEM;
		goto error;
	}

	whc_hw_reset(whc);

	/* Read maximum number of devices, keys and MMC IEs. */
	whcsparams = le_readl(whc->base + WHCSPARAMS);
	whc->n_devices = WHCSPARAMS_TO_N_DEVICES(whcsparams);
	whc->n_keys    = WHCSPARAMS_TO_N_KEYS(whcsparams);
	whc->n_mmc_ies = WHCSPARAMS_TO_N_MMC_IES(whcsparams);

	dev_dbg(&whc->umc->dev, "N_DEVICES = %d, N_KEYS = %d, N_MMC_IES = %d\n",
		whc->n_devices, whc->n_keys, whc->n_mmc_ies);

	whc->qset_pool = dma_pool_create("qset", &whc->umc->dev,
					 sizeof(struct whc_qset), 64, 0);
	if (whc->qset_pool == NULL) {
		ret = -ENOMEM;
		goto error;
	}

	ret = asl_init(whc);
	if (ret < 0)
		goto error;
	ret = pzl_init(whc);
	if (ret < 0)
		goto error;

	/* Allocate and initialize a buffer for generic commands, the
	   Device Information buffer, and the Device Notification
	   buffer. */

	whc->gen_cmd_buf = dma_alloc_coherent(&whc->umc->dev, WHC_GEN_CMD_DATA_LEN,
					      &whc->gen_cmd_buf_dma, GFP_KERNEL);
	if (whc->gen_cmd_buf == NULL) {
		ret = -ENOMEM;
		goto error;
	}

	whc->dn_buf = dma_alloc_coherent(&whc->umc->dev,
					 sizeof(struct dn_buf_entry) * WHC_N_DN_ENTRIES,
					 &whc->dn_buf_dma, GFP_KERNEL);
	if (!whc->dn_buf) {
		ret = -ENOMEM;
		goto error;
	}
	whc_hw_init_dn_buf(whc);

	whc->di_buf = dma_alloc_coherent(&whc->umc->dev,
					 sizeof(struct di_buf_entry) * whc->n_devices,
					 &whc->di_buf_dma, GFP_KERNEL);
	if (!whc->di_buf) {
		ret = -ENOMEM;
		goto error;
	}
	whc_hw_init_di_buf(whc);

	return 0;

error:
	whc_clean_up(whc);
	return ret;
}