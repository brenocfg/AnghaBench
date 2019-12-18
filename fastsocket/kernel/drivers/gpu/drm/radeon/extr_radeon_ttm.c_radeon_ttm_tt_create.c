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
typedef  int /*<<< orphan*/  uint32_t ;
struct ttm_tt {int /*<<< orphan*/ * func; } ;
struct ttm_bo_device {int dummy; } ;
struct TYPE_6__ {struct ttm_tt ttm; } ;
struct radeon_ttm_tt {TYPE_3__ ttm; struct radeon_device* rdev; } ;
struct radeon_device {int flags; TYPE_2__* ddev; } ;
struct page {int dummy; } ;
struct TYPE_5__ {TYPE_1__* agp; } ;
struct TYPE_4__ {int /*<<< orphan*/  bridge; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int RADEON_IS_AGP ; 
 int /*<<< orphan*/  kfree (struct radeon_ttm_tt*) ; 
 struct radeon_ttm_tt* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_backend_func ; 
 struct radeon_device* radeon_get_rdev (struct ttm_bo_device*) ; 
 struct ttm_tt* ttm_agp_tt_create (struct ttm_bo_device*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,struct page*) ; 
 scalar_t__ ttm_dma_tt_init (TYPE_3__*,struct ttm_bo_device*,unsigned long,int /*<<< orphan*/ ,struct page*) ; 

__attribute__((used)) static struct ttm_tt *radeon_ttm_tt_create(struct ttm_bo_device *bdev,
				    unsigned long size, uint32_t page_flags,
				    struct page *dummy_read_page)
{
	struct radeon_device *rdev;
	struct radeon_ttm_tt *gtt;

	rdev = radeon_get_rdev(bdev);
#if __OS_HAS_AGP
	if (rdev->flags & RADEON_IS_AGP) {
		return ttm_agp_tt_create(bdev, rdev->ddev->agp->bridge,
					 size, page_flags, dummy_read_page);
	}
#endif

	gtt = kzalloc(sizeof(struct radeon_ttm_tt), GFP_KERNEL);
	if (gtt == NULL) {
		return NULL;
	}
	gtt->ttm.ttm.func = &radeon_backend_func;
	gtt->rdev = rdev;
	if (ttm_dma_tt_init(&gtt->ttm, bdev, size, page_flags, dummy_read_page)) {
		kfree(gtt);
		return NULL;
	}
	return &gtt->ttm.ttm;
}