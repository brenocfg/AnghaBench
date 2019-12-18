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
struct intel_crtc {int* lut_r; int* lut_g; int* lut_b; int /*<<< orphan*/  pipe; int /*<<< orphan*/  active; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct drm_crtc {int /*<<< orphan*/  enabled; struct drm_device* dev; } ;

/* Variables and functions */
 scalar_t__ HAS_PCH_SPLIT (struct drm_device*) ; 
 int /*<<< orphan*/  I915_WRITE (int,int) ; 
 int LGC_PALETTE (int /*<<< orphan*/ ) ; 
 int PALETTE (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 

void intel_crtc_load_lut(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	int palreg = PALETTE(intel_crtc->pipe);
	int i;

	/* The clocks have to be on to load the palette. */
	if (!crtc->enabled || !intel_crtc->active)
		return;

	/* use legacy palette for Ironlake */
	if (HAS_PCH_SPLIT(dev))
		palreg = LGC_PALETTE(intel_crtc->pipe);

	for (i = 0; i < 256; i++) {
		I915_WRITE(palreg + 4 * i,
			   (intel_crtc->lut_r[i] << 16) |
			   (intel_crtc->lut_g[i] << 8) |
			   intel_crtc->lut_b[i]);
	}
}