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
typedef  int uint32_t ;
typedef  int u32 ;
struct intel_crtc {int pipe; int cursor_visible; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURBASE (int) ; 
 int /*<<< orphan*/  CURCNTR (int) ; 
 int CURSOR_MODE ; 
 int CURSOR_MODE_64_ARGB_AX ; 
 int CURSOR_MODE_DISABLE ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int MCURSOR_GAMMA_ENABLE ; 
 int MCURSOR_PIPE_SELECT ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void i9xx_update_cursor(struct drm_crtc *crtc, u32 base)
{
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	int pipe = intel_crtc->pipe;
	bool visible = base != 0;

	if (intel_crtc->cursor_visible != visible) {
		uint32_t cntl = I915_READ(CURCNTR(pipe));
		if (base) {
			cntl &= ~(CURSOR_MODE | MCURSOR_PIPE_SELECT);
			cntl |= CURSOR_MODE_64_ARGB_AX | MCURSOR_GAMMA_ENABLE;
			cntl |= pipe << 28; /* Connect to correct pipe */
		} else {
			cntl &= ~(CURSOR_MODE | MCURSOR_GAMMA_ENABLE);
			cntl |= CURSOR_MODE_DISABLE;
		}
		I915_WRITE(CURCNTR(pipe), cntl);

		intel_crtc->cursor_visible = visible;
	}
	/* and commit changes on next vblank */
	I915_WRITE(CURBASE(pipe), base);
}