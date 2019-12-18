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
typedef  int /*<<< orphan*/  uint32_t ;
struct ttm_tt {int dummy; } ;
struct ttm_bo_device {int dummy; } ;
struct page {int dummy; } ;
struct TYPE_3__ {scalar_t__ stat; } ;
struct nouveau_drm {TYPE_1__ agp; struct drm_device* dev; } ;
struct drm_device {TYPE_2__* agp; } ;
struct TYPE_4__ {int /*<<< orphan*/  bridge; } ;

/* Variables and functions */
 scalar_t__ ENABLED ; 
 struct nouveau_drm* nouveau_bdev (struct ttm_bo_device*) ; 
 struct ttm_tt* nouveau_sgdma_create_ttm (struct ttm_bo_device*,unsigned long,int /*<<< orphan*/ ,struct page*) ; 
 struct ttm_tt* ttm_agp_tt_create (struct ttm_bo_device*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,struct page*) ; 

__attribute__((used)) static struct ttm_tt *
nouveau_ttm_tt_create(struct ttm_bo_device *bdev, unsigned long size,
		      uint32_t page_flags, struct page *dummy_read)
{
#if __OS_HAS_AGP
	struct nouveau_drm *drm = nouveau_bdev(bdev);
	struct drm_device *dev = drm->dev;

	if (drm->agp.stat == ENABLED) {
		return ttm_agp_tt_create(bdev, dev->agp->bridge, size,
					 page_flags, dummy_read);
	}
#endif

	return nouveau_sgdma_create_ttm(bdev, size, page_flags, dummy_read);
}