#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int use_event; int enabled; scalar_t__ wb; int /*<<< orphan*/ * wb_obj; int /*<<< orphan*/  gpu_addr; } ;
struct radeon_device {int flags; scalar_t__ family; TYPE_1__ wb; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CHIP_PALM ; 
 scalar_t__ CHIP_R300 ; 
 scalar_t__ CHIP_R600 ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  RADEON_GEM_DOMAIN_GTT ; 
 int /*<<< orphan*/  RADEON_GPU_PAGE_SIZE ; 
 int RADEON_IS_AGP ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int radeon_bo_create (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int radeon_bo_kmap (int /*<<< orphan*/ *,void**) ; 
 int radeon_bo_pin (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int radeon_bo_reserve (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  radeon_bo_unreserve (int /*<<< orphan*/ *) ; 
 int radeon_no_wb ; 
 int /*<<< orphan*/  radeon_wb_fini (struct radeon_device*) ; 
 scalar_t__ unlikely (int) ; 

int radeon_wb_init(struct radeon_device *rdev)
{
	int r;

	if (rdev->wb.wb_obj == NULL) {
		r = radeon_bo_create(rdev, RADEON_GPU_PAGE_SIZE, PAGE_SIZE, true,
				     RADEON_GEM_DOMAIN_GTT, NULL, &rdev->wb.wb_obj);
		if (r) {
			dev_warn(rdev->dev, "(%d) create WB bo failed\n", r);
			return r;
		}
	}
	r = radeon_bo_reserve(rdev->wb.wb_obj, false);
	if (unlikely(r != 0)) {
		radeon_wb_fini(rdev);
		return r;
	}
	r = radeon_bo_pin(rdev->wb.wb_obj, RADEON_GEM_DOMAIN_GTT,
			  &rdev->wb.gpu_addr);
	if (r) {
		radeon_bo_unreserve(rdev->wb.wb_obj);
		dev_warn(rdev->dev, "(%d) pin WB bo failed\n", r);
		radeon_wb_fini(rdev);
		return r;
	}
	r = radeon_bo_kmap(rdev->wb.wb_obj, (void **)&rdev->wb.wb);
	radeon_bo_unreserve(rdev->wb.wb_obj);
	if (r) {
		dev_warn(rdev->dev, "(%d) map WB bo failed\n", r);
		radeon_wb_fini(rdev);
		return r;
	}

	/* clear wb memory */
	memset((char *)rdev->wb.wb, 0, RADEON_GPU_PAGE_SIZE);
	/* disable event_write fences */
	rdev->wb.use_event = false;
	/* disabled via module param */
	if (radeon_no_wb == 1) {
		rdev->wb.enabled = false;
	} else {
		if (rdev->flags & RADEON_IS_AGP) {
			/* often unreliable on AGP */
			rdev->wb.enabled = false;
		} else if (rdev->family < CHIP_R300) {
			/* often unreliable on pre-r300 */
			rdev->wb.enabled = false;
		} else {
			rdev->wb.enabled = true;
			/* event_write fences are only available on r600+ */
			if (rdev->family >= CHIP_R600) {
				rdev->wb.use_event = true;
			}
		}
	}
	/* always use writeback/events on NI, APUs */
	if (rdev->family >= CHIP_PALM) {
		rdev->wb.enabled = true;
		rdev->wb.use_event = true;
	}

	dev_info(rdev->dev, "WB %sabled\n", rdev->wb.enabled ? "en" : "dis");

	return 0;
}