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
struct TYPE_4__ {int mtrr; int /*<<< orphan*/  bdev; } ;
struct nouveau_drm {TYPE_2__ ttm; TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  pdev; int /*<<< orphan*/  struct_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MTRR_WC ; 
 int /*<<< orphan*/  TTM_PL_TT ; 
 int /*<<< orphan*/  TTM_PL_VRAM ; 
 int /*<<< orphan*/  drm_mtrr_del (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_ttm_global_release (struct nouveau_drm*) ; 
 int /*<<< orphan*/  pci_resource_len (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_resource_start (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ttm_bo_clean_mm (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_bo_device_release (int /*<<< orphan*/ *) ; 

void
nouveau_ttm_fini(struct nouveau_drm *drm)
{
	mutex_lock(&drm->dev->struct_mutex);
	ttm_bo_clean_mm(&drm->ttm.bdev, TTM_PL_VRAM);
	ttm_bo_clean_mm(&drm->ttm.bdev, TTM_PL_TT);
	mutex_unlock(&drm->dev->struct_mutex);

	ttm_bo_device_release(&drm->ttm.bdev);

	nouveau_ttm_global_release(drm);

	if (drm->ttm.mtrr >= 0) {
		drm_mtrr_del(drm->ttm.mtrr,
			     pci_resource_start(drm->dev->pdev, 1),
			     pci_resource_len(drm->dev->pdev, 1), DRM_MTRR_WC);
		drm->ttm.mtrr = -1;
	}
}