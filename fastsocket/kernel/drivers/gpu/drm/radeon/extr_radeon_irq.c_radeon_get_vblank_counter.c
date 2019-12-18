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
typedef  int /*<<< orphan*/  u32 ;
struct drm_device {TYPE_1__* dev_private; } ;
struct TYPE_2__ {int flags; } ;
typedef  TYPE_1__ drm_radeon_private_t ;

/* Variables and functions */
 int CHIP_RS600 ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  R500_D1CRTC_FRAME_COUNT ; 
 int /*<<< orphan*/  R500_D2CRTC_FRAME_COUNT ; 
 int /*<<< orphan*/  RADEON_CRTC2_CRNT_FRAME ; 
 int /*<<< orphan*/  RADEON_CRTC_CRNT_FRAME ; 
 int RADEON_FAMILY_MASK ; 
 int /*<<< orphan*/  RADEON_READ (int /*<<< orphan*/ ) ; 

u32 radeon_get_vblank_counter(struct drm_device *dev, int crtc)
{
	drm_radeon_private_t *dev_priv = dev->dev_private;

	if (!dev_priv) {
		DRM_ERROR("called with no initialization\n");
		return -EINVAL;
	}

	if (crtc < 0 || crtc > 1) {
		DRM_ERROR("Invalid crtc %d\n", crtc);
		return -EINVAL;
	}

	if ((dev_priv->flags & RADEON_FAMILY_MASK) >= CHIP_RS600) {
		if (crtc == 0)
			return RADEON_READ(R500_D1CRTC_FRAME_COUNT);
		else
			return RADEON_READ(R500_D2CRTC_FRAME_COUNT);
	} else {
		if (crtc == 0)
			return RADEON_READ(RADEON_CRTC_CRNT_FRAME);
		else
			return RADEON_READ(RADEON_CRTC2_CRNT_FRAME);
	}
}