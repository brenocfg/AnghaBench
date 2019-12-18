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
typedef  scalar_t__ u64 ;
struct srp_host {int /*<<< orphan*/  list; } ;
struct srp_device {int fmr_page_size; int fmr_max_size; int /*<<< orphan*/ * pd; int /*<<< orphan*/  dev_list; int /*<<< orphan*/ * fmr_pool; int /*<<< orphan*/ * mr; struct ib_device* dev; scalar_t__ fmr_page_mask; int /*<<< orphan*/  page_size_cap; } ;
struct ib_fmr_pool_param {int cache; int max_pages_per_fmr; int page_shift; int access; int /*<<< orphan*/  dirty_watermark; int /*<<< orphan*/  pool_size; } ;
struct ib_device_attr {int fmr_page_size; int fmr_max_size; int /*<<< orphan*/ * pd; int /*<<< orphan*/  dev_list; int /*<<< orphan*/ * fmr_pool; int /*<<< orphan*/ * mr; struct ib_device* dev; scalar_t__ fmr_page_mask; int /*<<< orphan*/  page_size_cap; } ;
struct ib_device {scalar_t__ node_type; int phys_port_cnt; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IB_ACCESS_LOCAL_WRITE ; 
 int IB_ACCESS_REMOTE_READ ; 
 int IB_ACCESS_REMOTE_WRITE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ RDMA_NODE_IB_SWITCH ; 
 int /*<<< orphan*/  SRP_FMR_DIRTY_SIZE ; 
 int SRP_FMR_MIN_SIZE ; 
 int /*<<< orphan*/  SRP_FMR_POOL_SIZE ; 
 int SRP_FMR_SIZE ; 
 scalar_t__ ffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ib_alloc_pd (struct ib_device*) ; 
 int /*<<< orphan*/ * ib_create_fmr_pool (int /*<<< orphan*/ *,struct ib_fmr_pool_param*) ; 
 int /*<<< orphan*/  ib_dealloc_pd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ib_get_dma_mr (int /*<<< orphan*/ *,int) ; 
 scalar_t__ ib_query_device (struct ib_device*,struct srp_device*) ; 
 int /*<<< orphan*/  ib_set_client_data (struct ib_device*,int /*<<< orphan*/ *,struct srp_device*) ; 
 int /*<<< orphan*/  kfree (struct srp_device*) ; 
 struct srp_device* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int max (int,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct ib_fmr_pool_param*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 struct srp_host* srp_add_port (struct srp_device*,int) ; 
 int /*<<< orphan*/  srp_client ; 

__attribute__((used)) static void srp_add_one(struct ib_device *device)
{
	struct srp_device *srp_dev;
	struct ib_device_attr *dev_attr;
	struct ib_fmr_pool_param fmr_param;
	struct srp_host *host;
	int max_pages_per_fmr, fmr_page_shift, s, e, p;

	dev_attr = kmalloc(sizeof *dev_attr, GFP_KERNEL);
	if (!dev_attr)
		return;

	if (ib_query_device(device, dev_attr)) {
		pr_warn("Query device failed for %s\n", device->name);
		goto free_attr;
	}

	srp_dev = kmalloc(sizeof *srp_dev, GFP_KERNEL);
	if (!srp_dev)
		goto free_attr;

	/*
	 * Use the smallest page size supported by the HCA, down to a
	 * minimum of 4096 bytes. We're unlikely to build large sglists
	 * out of smaller entries.
	 */
	fmr_page_shift		= max(12, ffs(dev_attr->page_size_cap) - 1);
	srp_dev->fmr_page_size	= 1 << fmr_page_shift;
	srp_dev->fmr_page_mask	= ~((u64) srp_dev->fmr_page_size - 1);
	srp_dev->fmr_max_size	= srp_dev->fmr_page_size * SRP_FMR_SIZE;

	INIT_LIST_HEAD(&srp_dev->dev_list);

	srp_dev->dev = device;
	srp_dev->pd  = ib_alloc_pd(device);
	if (IS_ERR(srp_dev->pd))
		goto free_dev;

	srp_dev->mr = ib_get_dma_mr(srp_dev->pd,
				    IB_ACCESS_LOCAL_WRITE |
				    IB_ACCESS_REMOTE_READ |
				    IB_ACCESS_REMOTE_WRITE);
	if (IS_ERR(srp_dev->mr))
		goto err_pd;

	for (max_pages_per_fmr = SRP_FMR_SIZE;
			max_pages_per_fmr >= SRP_FMR_MIN_SIZE;
			max_pages_per_fmr /= 2, srp_dev->fmr_max_size /= 2) {
		memset(&fmr_param, 0, sizeof fmr_param);
		fmr_param.pool_size	    = SRP_FMR_POOL_SIZE;
		fmr_param.dirty_watermark   = SRP_FMR_DIRTY_SIZE;
		fmr_param.cache		    = 1;
		fmr_param.max_pages_per_fmr = max_pages_per_fmr;
		fmr_param.page_shift	    = fmr_page_shift;
		fmr_param.access	    = (IB_ACCESS_LOCAL_WRITE |
					       IB_ACCESS_REMOTE_WRITE |
					       IB_ACCESS_REMOTE_READ);

		srp_dev->fmr_pool = ib_create_fmr_pool(srp_dev->pd, &fmr_param);
		if (!IS_ERR(srp_dev->fmr_pool))
			break;
	}

	if (IS_ERR(srp_dev->fmr_pool))
		srp_dev->fmr_pool = NULL;

	if (device->node_type == RDMA_NODE_IB_SWITCH) {
		s = 0;
		e = 0;
	} else {
		s = 1;
		e = device->phys_port_cnt;
	}

	for (p = s; p <= e; ++p) {
		host = srp_add_port(srp_dev, p);
		if (host)
			list_add_tail(&host->list, &srp_dev->dev_list);
	}

	ib_set_client_data(device, &srp_client, srp_dev);

	goto free_attr;

err_pd:
	ib_dealloc_pd(srp_dev->pd);

free_dev:
	kfree(srp_dev);

free_attr:
	kfree(dev_attr);
}