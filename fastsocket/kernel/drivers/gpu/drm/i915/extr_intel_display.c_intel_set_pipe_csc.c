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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct intel_crtc {int pipe; } ;
struct drm_i915_private {int dummy; } ;
struct drm_display_mode {int private_flags; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;
struct TYPE_2__ {int gen; } ;

/* Variables and functions */
 int CSC_BLACK_SCREEN_OFFSET ; 
 int CSC_MODE_YUV_TO_RGB ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* INTEL_INFO (struct drm_device*) ; 
 int INTEL_MODE_LIMITED_COLOR_RANGE ; 
 int /*<<< orphan*/  PIPE_CSC_COEFF_BU (int) ; 
 int /*<<< orphan*/  PIPE_CSC_COEFF_BV (int) ; 
 int /*<<< orphan*/  PIPE_CSC_COEFF_BY (int) ; 
 int /*<<< orphan*/  PIPE_CSC_COEFF_RU_GU (int) ; 
 int /*<<< orphan*/  PIPE_CSC_COEFF_RV_GV (int) ; 
 int /*<<< orphan*/  PIPE_CSC_COEFF_RY_GY (int) ; 
 int /*<<< orphan*/  PIPE_CSC_MODE (int) ; 
 int /*<<< orphan*/  PIPE_CSC_POSTOFF_HI (int) ; 
 int /*<<< orphan*/  PIPE_CSC_POSTOFF_LO (int) ; 
 int /*<<< orphan*/  PIPE_CSC_POSTOFF_ME (int) ; 
 int /*<<< orphan*/  PIPE_CSC_PREOFF_HI (int) ; 
 int /*<<< orphan*/  PIPE_CSC_PREOFF_LO (int) ; 
 int /*<<< orphan*/  PIPE_CSC_PREOFF_ME (int) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void intel_set_pipe_csc(struct drm_crtc *crtc,
			       const struct drm_display_mode *adjusted_mode)
{
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	int pipe = intel_crtc->pipe;
	uint16_t coeff = 0x7800; /* 1.0 */

	/*
	 * TODO: Check what kind of values actually come out of the pipe
	 * with these coeff/postoff values and adjust to get the best
	 * accuracy. Perhaps we even need to take the bpc value into
	 * consideration.
	 */

	if (adjusted_mode->private_flags & INTEL_MODE_LIMITED_COLOR_RANGE)
		coeff = ((235 - 16) * (1 << 12) / 255) & 0xff8; /* 0.xxx... */

	/*
	 * GY/GU and RY/RU should be the other way around according
	 * to BSpec, but reality doesn't agree. Just set them up in
	 * a way that results in the correct picture.
	 */
	I915_WRITE(PIPE_CSC_COEFF_RY_GY(pipe), coeff << 16);
	I915_WRITE(PIPE_CSC_COEFF_BY(pipe), 0);

	I915_WRITE(PIPE_CSC_COEFF_RU_GU(pipe), coeff);
	I915_WRITE(PIPE_CSC_COEFF_BU(pipe), 0);

	I915_WRITE(PIPE_CSC_COEFF_RV_GV(pipe), 0);
	I915_WRITE(PIPE_CSC_COEFF_BV(pipe), coeff << 16);

	I915_WRITE(PIPE_CSC_PREOFF_HI(pipe), 0);
	I915_WRITE(PIPE_CSC_PREOFF_ME(pipe), 0);
	I915_WRITE(PIPE_CSC_PREOFF_LO(pipe), 0);

	if (INTEL_INFO(dev)->gen > 6) {
		uint16_t postoff = 0;

		if (adjusted_mode->private_flags & INTEL_MODE_LIMITED_COLOR_RANGE)
			postoff = (16 * (1 << 13) / 255) & 0x1fff;

		I915_WRITE(PIPE_CSC_POSTOFF_HI(pipe), postoff);
		I915_WRITE(PIPE_CSC_POSTOFF_ME(pipe), postoff);
		I915_WRITE(PIPE_CSC_POSTOFF_LO(pipe), postoff);

		I915_WRITE(PIPE_CSC_MODE(pipe), 0);
	} else {
		uint32_t mode = CSC_MODE_YUV_TO_RGB;

		if (adjusted_mode->private_flags & INTEL_MODE_LIMITED_COLOR_RANGE)
			mode |= CSC_BLACK_SCREEN_OFFSET;

		I915_WRITE(PIPE_CSC_MODE(pipe), mode);
	}
}