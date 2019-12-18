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
typedef  int /*<<< orphan*/  uint64_t ;
struct ttm_bo_global {int /*<<< orphan*/  device_list_mutex; int /*<<< orphan*/  device_list; } ;
struct ttm_bo_driver {int dummy; } ;
struct ttm_bo_device {int need_dma32; int /*<<< orphan*/  device_list; int /*<<< orphan*/  fence_lock; scalar_t__ val_seq; struct ttm_bo_global* glob; int /*<<< orphan*/ * dev_mapping; int /*<<< orphan*/  ddestroy; int /*<<< orphan*/  wq; int /*<<< orphan*/  addr_space_mm; int /*<<< orphan*/  addr_space_rb; int /*<<< orphan*/  man; struct ttm_bo_driver* driver; int /*<<< orphan*/  vm_lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  TTM_PL_SYSTEM ; 
 int drm_mm_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_clean_mm (struct ttm_bo_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_bo_delayed_workqueue ; 
 int ttm_bo_init_mm (struct ttm_bo_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int ttm_bo_device_init(struct ttm_bo_device *bdev,
		       struct ttm_bo_global *glob,
		       struct ttm_bo_driver *driver,
		       uint64_t file_page_offset,
		       bool need_dma32)
{
	int ret = -EINVAL;

	rwlock_init(&bdev->vm_lock);
	bdev->driver = driver;

	memset(bdev->man, 0, sizeof(bdev->man));

	/*
	 * Initialize the system memory buffer type.
	 * Other types need to be driver / IOCTL initialized.
	 */
	ret = ttm_bo_init_mm(bdev, TTM_PL_SYSTEM, 0);
	if (unlikely(ret != 0))
		goto out_no_sys;

	bdev->addr_space_rb = RB_ROOT;
	ret = drm_mm_init(&bdev->addr_space_mm, file_page_offset, 0x10000000);
	if (unlikely(ret != 0))
		goto out_no_addr_mm;

	INIT_DELAYED_WORK(&bdev->wq, ttm_bo_delayed_workqueue);
	INIT_LIST_HEAD(&bdev->ddestroy);
	bdev->dev_mapping = NULL;
	bdev->glob = glob;
	bdev->need_dma32 = need_dma32;
	bdev->val_seq = 0;
	spin_lock_init(&bdev->fence_lock);
	mutex_lock(&glob->device_list_mutex);
	list_add_tail(&bdev->device_list, &glob->device_list);
	mutex_unlock(&glob->device_list_mutex);

	return 0;
out_no_addr_mm:
	ttm_bo_clean_mm(bdev, 0);
out_no_sys:
	return ret;
}