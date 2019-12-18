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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u32 ;
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,...) ; 
 int I915_READ (int) ; 
 int /*<<< orphan*/  I915_WRITE (int,int) ; 
 int /*<<< orphan*/  IS_IVYBRIDGE (struct drm_device*) ; 
 int SNB_READ_WM0_LATENCY () ; 
 int SNB_READ_WM1_LATENCY () ; 
 int SNB_READ_WM2_LATENCY () ; 
 int SNB_READ_WM3_LATENCY () ; 
 int WM0_PIPEA_ILK ; 
 int WM0_PIPEB_ILK ; 
 int WM0_PIPEC_IVB ; 
 int WM0_PIPE_SPRITE_MASK ; 
 int WM0_PIPE_SPRITE_SHIFT ; 
 int WM1S_LP_ILK ; 
 int WM2S_LP_IVB ; 
 int WM3S_LP_IVB ; 
 int sandybridge_compute_sprite_srwm (struct drm_device*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int*) ; 
 int sandybridge_compute_sprite_wm (struct drm_device*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  sandybridge_display_srwm_info ; 
 int /*<<< orphan*/  sandybridge_display_wm_info ; 

__attribute__((used)) static void sandybridge_update_sprite_wm(struct drm_device *dev, int pipe,
					 uint32_t sprite_width, int pixel_size)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int latency = SNB_READ_WM0_LATENCY() * 100;	/* In unit 0.1us */
	u32 val;
	int sprite_wm, reg;
	int ret;

	switch (pipe) {
	case 0:
		reg = WM0_PIPEA_ILK;
		break;
	case 1:
		reg = WM0_PIPEB_ILK;
		break;
	case 2:
		reg = WM0_PIPEC_IVB;
		break;
	default:
		return; /* bad pipe */
	}

	ret = sandybridge_compute_sprite_wm(dev, pipe, sprite_width, pixel_size,
					    &sandybridge_display_wm_info,
					    latency, &sprite_wm);
	if (!ret) {
		DRM_DEBUG_KMS("failed to compute sprite wm for pipe %d\n",
			      pipe);
		return;
	}

	val = I915_READ(reg);
	val &= ~WM0_PIPE_SPRITE_MASK;
	I915_WRITE(reg, val | (sprite_wm << WM0_PIPE_SPRITE_SHIFT));
	DRM_DEBUG_KMS("sprite watermarks For pipe %d - %d\n", pipe, sprite_wm);


	ret = sandybridge_compute_sprite_srwm(dev, pipe, sprite_width,
					      pixel_size,
					      &sandybridge_display_srwm_info,
					      SNB_READ_WM1_LATENCY() * 500,
					      &sprite_wm);
	if (!ret) {
		DRM_DEBUG_KMS("failed to compute sprite lp1 wm on pipe %d\n",
			      pipe);
		return;
	}
	I915_WRITE(WM1S_LP_ILK, sprite_wm);

	/* Only IVB has two more LP watermarks for sprite */
	if (!IS_IVYBRIDGE(dev))
		return;

	ret = sandybridge_compute_sprite_srwm(dev, pipe, sprite_width,
					      pixel_size,
					      &sandybridge_display_srwm_info,
					      SNB_READ_WM2_LATENCY() * 500,
					      &sprite_wm);
	if (!ret) {
		DRM_DEBUG_KMS("failed to compute sprite lp2 wm on pipe %d\n",
			      pipe);
		return;
	}
	I915_WRITE(WM2S_LP_IVB, sprite_wm);

	ret = sandybridge_compute_sprite_srwm(dev, pipe, sprite_width,
					      pixel_size,
					      &sandybridge_display_srwm_info,
					      SNB_READ_WM3_LATENCY() * 500,
					      &sprite_wm);
	if (!ret) {
		DRM_DEBUG_KMS("failed to compute sprite lp3 wm on pipe %d\n",
			      pipe);
		return;
	}
	I915_WRITE(WM3S_LP_IVB, sprite_wm);
}