#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_12__ {int gtt_size; scalar_t__ gtt_end; scalar_t__ gtt_start; scalar_t__ agp_base; } ;
struct radeon_device {scalar_t__ family; TYPE_4__ mc; int /*<<< orphan*/  dev; TYPE_5__* ddev; TYPE_1__* pdev; } ;
struct radeon_agpmode_quirk {scalar_t__ chip_device; scalar_t__ hostbridge_vendor; scalar_t__ hostbridge_device; scalar_t__ chip_vendor; scalar_t__ subsys_vendor; scalar_t__ subsys_device; int default_mode; } ;
struct drm_agp_mode {int mode; } ;
struct drm_agp_info {int mode; scalar_t__ id_vendor; scalar_t__ id_device; } ;
struct TYPE_13__ {TYPE_3__* agp; } ;
struct TYPE_10__ {int aper_size; scalar_t__ aper_base; } ;
struct TYPE_11__ {TYPE_2__ agp_info; } ;
struct TYPE_9__ {scalar_t__ vendor; scalar_t__ device; scalar_t__ subsystem_vendor; scalar_t__ subsystem_device; } ;

/* Variables and functions */
 scalar_t__ CHIP_R200 ; 
 scalar_t__ CHIP_RV350 ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,...) ; 
 int /*<<< orphan*/  DRM_INFO (char*,int) ; 
 int EINVAL ; 
 int RADEON_AGP_1X_MODE ; 
 int RADEON_AGP_2X_MODE ; 
 int RADEON_AGP_4X_MODE ; 
 int /*<<< orphan*/  RADEON_AGP_CNTL ; 
 int RADEON_AGP_FW_MODE ; 
 int RADEON_AGP_MODE_MASK ; 
 int /*<<< orphan*/  RADEON_AGP_STATUS ; 
 int RADEON_AGPv3_4X_MODE ; 
 int RADEON_AGPv3_8X_MODE ; 
 int RADEON_AGPv3_MODE ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int drm_agp_acquire (TYPE_5__*) ; 
 int drm_agp_enable (TYPE_5__*,struct drm_agp_mode) ; 
 int drm_agp_info (TYPE_5__*,struct drm_agp_info*) ; 
 int /*<<< orphan*/  drm_agp_release (TYPE_5__*) ; 
 int radeon_agpmode ; 
 struct radeon_agpmode_quirk* radeon_agpmode_quirk_list ; 

int radeon_agp_init(struct radeon_device *rdev)
{
#if __OS_HAS_AGP
	struct radeon_agpmode_quirk *p = radeon_agpmode_quirk_list;
	struct drm_agp_mode mode;
	struct drm_agp_info info;
	uint32_t agp_status;
	int default_mode;
	bool is_v3;
	int ret;

	/* Acquire AGP. */
	ret = drm_agp_acquire(rdev->ddev);
	if (ret) {
		DRM_ERROR("Unable to acquire AGP: %d\n", ret);
		return ret;
	}

	ret = drm_agp_info(rdev->ddev, &info);
	if (ret) {
		drm_agp_release(rdev->ddev);
		DRM_ERROR("Unable to get AGP info: %d\n", ret);
		return ret;
	}

	if (rdev->ddev->agp->agp_info.aper_size < 32) {
		drm_agp_release(rdev->ddev);
		dev_warn(rdev->dev, "AGP aperture too small (%zuM) "
			"need at least 32M, disabling AGP\n",
			rdev->ddev->agp->agp_info.aper_size);
		return -EINVAL;
	}

	mode.mode = info.mode;
	/* chips with the agp to pcie bridge don't have the AGP_STATUS register
	 * Just use the whatever mode the host sets up.
	 */
	if (rdev->family <= CHIP_RV350)
		agp_status = (RREG32(RADEON_AGP_STATUS) | RADEON_AGPv3_MODE) & mode.mode;
	else
		agp_status = mode.mode;
	is_v3 = !!(agp_status & RADEON_AGPv3_MODE);

	if (is_v3) {
		default_mode = (agp_status & RADEON_AGPv3_8X_MODE) ? 8 : 4;
	} else {
		if (agp_status & RADEON_AGP_4X_MODE) {
			default_mode = 4;
		} else if (agp_status & RADEON_AGP_2X_MODE) {
			default_mode = 2;
		} else {
			default_mode = 1;
		}
	}

	/* Apply AGPMode Quirks */
	while (p && p->chip_device != 0) {
		if (info.id_vendor == p->hostbridge_vendor &&
		    info.id_device == p->hostbridge_device &&
		    rdev->pdev->vendor == p->chip_vendor &&
		    rdev->pdev->device == p->chip_device &&
		    rdev->pdev->subsystem_vendor == p->subsys_vendor &&
		    rdev->pdev->subsystem_device == p->subsys_device) {
			default_mode = p->default_mode;
		}
		++p;
	}

	if (radeon_agpmode > 0) {
		if ((radeon_agpmode < (is_v3 ? 4 : 1)) ||
		    (radeon_agpmode > (is_v3 ? 8 : 4)) ||
		    (radeon_agpmode & (radeon_agpmode - 1))) {
			DRM_ERROR("Illegal AGP Mode: %d (valid %s), leaving at %d\n",
				  radeon_agpmode, is_v3 ? "4, 8" : "1, 2, 4",
				  default_mode);
			radeon_agpmode = default_mode;
		} else {
			DRM_INFO("AGP mode requested: %d\n", radeon_agpmode);
		}
	} else {
		radeon_agpmode = default_mode;
	}

	mode.mode &= ~RADEON_AGP_MODE_MASK;
	if (is_v3) {
		switch (radeon_agpmode) {
		case 8:
			mode.mode |= RADEON_AGPv3_8X_MODE;
			break;
		case 4:
		default:
			mode.mode |= RADEON_AGPv3_4X_MODE;
			break;
		}
	} else {
		switch (radeon_agpmode) {
		case 4:
			mode.mode |= RADEON_AGP_4X_MODE;
			break;
		case 2:
			mode.mode |= RADEON_AGP_2X_MODE;
			break;
		case 1:
		default:
			mode.mode |= RADEON_AGP_1X_MODE;
			break;
		}
	}

	mode.mode &= ~RADEON_AGP_FW_MODE; /* disable fw */
	ret = drm_agp_enable(rdev->ddev, mode);
	if (ret) {
		DRM_ERROR("Unable to enable AGP (mode = 0x%lx)\n", mode.mode);
		drm_agp_release(rdev->ddev);
		return ret;
	}

	rdev->mc.agp_base = rdev->ddev->agp->agp_info.aper_base;
	rdev->mc.gtt_size = rdev->ddev->agp->agp_info.aper_size << 20;
	rdev->mc.gtt_start = rdev->mc.agp_base;
	rdev->mc.gtt_end = rdev->mc.gtt_start + rdev->mc.gtt_size - 1;
	dev_info(rdev->dev, "GTT: %lluM 0x%08llX - 0x%08llX\n",
		rdev->mc.gtt_size >> 20, rdev->mc.gtt_start, rdev->mc.gtt_end);

	/* workaround some hw issues */
	if (rdev->family < CHIP_R200) {
		WREG32(RADEON_AGP_CNTL, RREG32(RADEON_AGP_CNTL) | 0x000e0000);
	}
	return 0;
#else
	return 0;
#endif
}