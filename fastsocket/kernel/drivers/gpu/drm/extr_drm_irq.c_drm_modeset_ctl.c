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
struct drm_modeset_ctl {unsigned int crtc; int cmd; } ;
struct drm_file {int dummy; } ;
struct drm_device {unsigned int num_crtcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_MODESET ; 
 int EINVAL ; 
#define  _DRM_POST_MODESET 129 
#define  _DRM_PRE_MODESET 128 
 scalar_t__ drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_vblank_post_modeset (struct drm_device*,unsigned int) ; 
 int /*<<< orphan*/  drm_vblank_pre_modeset (struct drm_device*,unsigned int) ; 

int drm_modeset_ctl(struct drm_device *dev, void *data,
		    struct drm_file *file_priv)
{
	struct drm_modeset_ctl *modeset = data;
	unsigned int crtc;

	/* If drm_vblank_init() hasn't been called yet, just no-op */
	if (!dev->num_crtcs)
		return 0;

	/* KMS drivers handle this internally */
	if (drm_core_check_feature(dev, DRIVER_MODESET))
		return 0;

	crtc = modeset->crtc;
	if (crtc >= dev->num_crtcs)
		return -EINVAL;

	switch (modeset->cmd) {
	case _DRM_PRE_MODESET:
		drm_vblank_pre_modeset(dev, crtc);
		break;
	case _DRM_POST_MODESET:
		drm_vblank_post_modeset(dev, crtc);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}