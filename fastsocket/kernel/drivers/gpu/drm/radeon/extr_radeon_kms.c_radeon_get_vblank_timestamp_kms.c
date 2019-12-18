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
struct timeval {int dummy; } ;
struct TYPE_4__ {TYPE_1__** crtcs; } ;
struct radeon_device {TYPE_2__ mode_info; } ;
struct drm_device {int num_crtcs; struct radeon_device* dev_private; } ;
struct drm_crtc {int dummy; } ;
struct TYPE_3__ {struct drm_crtc base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int EINVAL ; 
 int drm_calc_vbltimestamp_from_scanoutpos (struct drm_device*,int,int*,struct timeval*,unsigned int,struct drm_crtc*) ; 

int radeon_get_vblank_timestamp_kms(struct drm_device *dev, int crtc,
				    int *max_error,
				    struct timeval *vblank_time,
				    unsigned flags)
{
	struct drm_crtc *drmcrtc;
	struct radeon_device *rdev = dev->dev_private;

	if (crtc < 0 || crtc >= dev->num_crtcs) {
		DRM_ERROR("Invalid crtc %d\n", crtc);
		return -EINVAL;
	}

	/* Get associated drm_crtc: */
	drmcrtc = &rdev->mode_info.crtcs[crtc]->base;

	/* Helper routine in DRM core does all the work: */
	return drm_calc_vbltimestamp_from_scanoutpos(dev, crtc, max_error,
						     vblank_time, flags,
						     drmcrtc);
}