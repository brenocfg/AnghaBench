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
typedef  int u32 ;
struct intel_framebuffer {struct drm_i915_gem_object* obj; } ;
struct intel_crtc {int /*<<< orphan*/  plane; } ;
struct drm_i915_private {int dummy; } ;
struct drm_i915_gem_object {int fence_reg; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct drm_crtc {unsigned long y; struct drm_framebuffer* fb; struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPFC_CHICKEN ; 
 int /*<<< orphan*/  DPFC_CONTROL ; 
 unsigned long DPFC_CTL_EN ; 
 int DPFC_CTL_FENCE_EN ; 
 int DPFC_CTL_LIMIT_1X ; 
 int DPFC_CTL_PLANEA ; 
 int DPFC_CTL_PLANEB ; 
 int /*<<< orphan*/  DPFC_FENCE_YOFF ; 
 unsigned long DPFC_HT_MODIFY ; 
 int /*<<< orphan*/  DPFC_RECOMP_CTL ; 
 unsigned long DPFC_RECOMP_STALL_EN ; 
 unsigned long DPFC_RECOMP_STALL_WM_SHIFT ; 
 unsigned long DPFC_RECOMP_TIMER_COUNT_SHIFT ; 
 int DPFC_SR_EN ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 unsigned long I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,unsigned long) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 
 struct intel_framebuffer* to_intel_framebuffer (struct drm_framebuffer*) ; 

__attribute__((used)) static void g4x_enable_fbc(struct drm_crtc *crtc, unsigned long interval)
{
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct drm_framebuffer *fb = crtc->fb;
	struct intel_framebuffer *intel_fb = to_intel_framebuffer(fb);
	struct drm_i915_gem_object *obj = intel_fb->obj;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	int plane = intel_crtc->plane == 0 ? DPFC_CTL_PLANEA : DPFC_CTL_PLANEB;
	unsigned long stall_watermark = 200;
	u32 dpfc_ctl;

	dpfc_ctl = plane | DPFC_SR_EN | DPFC_CTL_LIMIT_1X;
	dpfc_ctl |= DPFC_CTL_FENCE_EN | obj->fence_reg;
	I915_WRITE(DPFC_CHICKEN, DPFC_HT_MODIFY);

	I915_WRITE(DPFC_RECOMP_CTL, DPFC_RECOMP_STALL_EN |
		   (stall_watermark << DPFC_RECOMP_STALL_WM_SHIFT) |
		   (interval << DPFC_RECOMP_TIMER_COUNT_SHIFT));
	I915_WRITE(DPFC_FENCE_YOFF, crtc->y);

	/* enable it... */
	I915_WRITE(DPFC_CONTROL, I915_READ(DPFC_CONTROL) | DPFC_CTL_EN);

	DRM_DEBUG_KMS("enabled fbc on plane %d\n", intel_crtc->plane);
}