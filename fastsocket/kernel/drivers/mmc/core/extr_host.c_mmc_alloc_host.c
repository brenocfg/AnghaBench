#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  notifier_call; } ;
struct TYPE_5__ {int /*<<< orphan*/ * class; struct device* parent; } ;
struct mmc_host {int max_hw_segs; int max_phys_segs; int max_seg_size; int max_req_size; int max_blk_size; int max_blk_count; TYPE_1__ pm_notify; int /*<<< orphan*/  disable; int /*<<< orphan*/  detect; int /*<<< orphan*/  wq; int /*<<< orphan*/  lock; TYPE_2__ class_dev; struct device* parent; int /*<<< orphan*/  index; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK_DEFERRABLE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  dev_set_name (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_initialize (TYPE_2__*) ; 
 int idr_get_new (int /*<<< orphan*/ *,struct mmc_host*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mmc_host*) ; 
 struct mmc_host* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_host_class ; 
 int /*<<< orphan*/  mmc_host_deeper_disable ; 
 int /*<<< orphan*/  mmc_host_idr ; 
 int /*<<< orphan*/  mmc_host_lock ; 
 int /*<<< orphan*/  mmc_pm_notify ; 
 int /*<<< orphan*/  mmc_rescan ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct mmc_host *mmc_alloc_host(int extra, struct device *dev)
{
	int err;
	struct mmc_host *host;

	if (!idr_pre_get(&mmc_host_idr, GFP_KERNEL))
		return NULL;

	host = kzalloc(sizeof(struct mmc_host) + extra, GFP_KERNEL);
	if (!host)
		return NULL;

	spin_lock(&mmc_host_lock);
	err = idr_get_new(&mmc_host_idr, host, &host->index);
	spin_unlock(&mmc_host_lock);
	if (err)
		goto free;

	dev_set_name(&host->class_dev, "mmc%d", host->index);

	host->parent = dev;
	host->class_dev.parent = dev;
	host->class_dev.class = &mmc_host_class;
	device_initialize(&host->class_dev);

	spin_lock_init(&host->lock);
	init_waitqueue_head(&host->wq);
	INIT_DELAYED_WORK(&host->detect, mmc_rescan);
	INIT_DELAYED_WORK_DEFERRABLE(&host->disable, mmc_host_deeper_disable);
	host->pm_notify.notifier_call = mmc_pm_notify;


	/*
	 * By default, hosts do not support SGIO or large requests.
	 * They have to set these according to their abilities.
	 */
	host->max_hw_segs = 1;
	host->max_phys_segs = 1;
	host->max_seg_size = PAGE_CACHE_SIZE;

	host->max_req_size = PAGE_CACHE_SIZE;
	host->max_blk_size = 512;
	host->max_blk_count = PAGE_CACHE_SIZE / 512;

	return host;

free:
	kfree(host);
	return NULL;
}