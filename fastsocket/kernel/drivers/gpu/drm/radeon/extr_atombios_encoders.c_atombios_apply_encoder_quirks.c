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
typedef  int /*<<< orphan*/  uint32_t ;
struct radeon_encoder {int devices; int active_device; } ;
struct radeon_device {int dummy; } ;
struct radeon_crtc {scalar_t__ crtc_offset; } ;
struct drm_encoder {int /*<<< orphan*/  crtc; struct drm_device* dev; } ;
struct drm_display_mode {int flags; } ;
struct drm_device {TYPE_1__* pdev; struct radeon_device* dev_private; } ;
struct TYPE_2__ {int device; int subsystem_vendor; int subsystem_device; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_AVIVO (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE4 (struct radeon_device*) ; 
 int ATOM_DEVICE_LCD1_SUPPORT ; 
 int ATOM_DEVICE_TV_SUPPORT ; 
 scalar_t__ AVIVO_D1MODE_DATA_FORMAT ; 
 int /*<<< orphan*/  AVIVO_D1MODE_INTERLEAVE_EN ; 
 scalar_t__ AVIVO_LVTMA_BIT_DEPTH_CONTROL ; 
 int /*<<< orphan*/  AVIVO_LVTMA_BIT_DEPTH_CONTROL_SPATIAL_DITHER_EN ; 
 int /*<<< orphan*/  AVIVO_LVTMA_BIT_DEPTH_CONTROL_TRUNCATE_EN ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 scalar_t__ EVERGREEN_DATA_FORMAT ; 
 int /*<<< orphan*/  EVERGREEN_INTERLEAVE_EN ; 
 int /*<<< orphan*/  RREG32 (scalar_t__) ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int /*<<< orphan*/ ) ; 
 struct radeon_crtc* to_radeon_crtc (int /*<<< orphan*/ ) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void
atombios_apply_encoder_quirks(struct drm_encoder *encoder,
			      struct drm_display_mode *mode)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	struct radeon_crtc *radeon_crtc = to_radeon_crtc(encoder->crtc);

	/* Funky macbooks */
	if ((dev->pdev->device == 0x71C5) &&
	    (dev->pdev->subsystem_vendor == 0x106b) &&
	    (dev->pdev->subsystem_device == 0x0080)) {
		if (radeon_encoder->devices & ATOM_DEVICE_LCD1_SUPPORT) {
			uint32_t lvtma_bit_depth_control = RREG32(AVIVO_LVTMA_BIT_DEPTH_CONTROL);

			lvtma_bit_depth_control &= ~AVIVO_LVTMA_BIT_DEPTH_CONTROL_TRUNCATE_EN;
			lvtma_bit_depth_control &= ~AVIVO_LVTMA_BIT_DEPTH_CONTROL_SPATIAL_DITHER_EN;

			WREG32(AVIVO_LVTMA_BIT_DEPTH_CONTROL, lvtma_bit_depth_control);
		}
	}

	/* set scaler clears this on some chips */
	if (ASIC_IS_AVIVO(rdev) &&
	    (!(radeon_encoder->active_device & (ATOM_DEVICE_TV_SUPPORT)))) {
		if (ASIC_IS_DCE4(rdev)) {
			if (mode->flags & DRM_MODE_FLAG_INTERLACE)
				WREG32(EVERGREEN_DATA_FORMAT + radeon_crtc->crtc_offset,
				       EVERGREEN_INTERLEAVE_EN);
			else
				WREG32(EVERGREEN_DATA_FORMAT + radeon_crtc->crtc_offset, 0);
		} else {
			if (mode->flags & DRM_MODE_FLAG_INTERLACE)
				WREG32(AVIVO_D1MODE_DATA_FORMAT + radeon_crtc->crtc_offset,
				       AVIVO_D1MODE_INTERLEAVE_EN);
			else
				WREG32(AVIVO_D1MODE_DATA_FORMAT + radeon_crtc->crtc_offset, 0);
		}
	}
}