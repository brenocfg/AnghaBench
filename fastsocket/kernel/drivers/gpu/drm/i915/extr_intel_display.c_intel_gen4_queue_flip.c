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
struct intel_ring_buffer {int dummy; } ;
struct intel_crtc {int dspaddr_offset; int /*<<< orphan*/  pipe; int /*<<< orphan*/  plane; } ;
struct drm_i915_private {struct intel_ring_buffer* ring; } ;
struct drm_i915_gem_object {int gtt_offset; int tiling_mode; } ;
struct drm_framebuffer {int* pitches; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int I915_READ (int /*<<< orphan*/ ) ; 
 int MI_DISPLAY_FLIP ; 
 int MI_DISPLAY_FLIP_PLANE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPESRC (int /*<<< orphan*/ ) ; 
 size_t RCS ; 
 int /*<<< orphan*/  intel_mark_page_flip_active (struct intel_crtc*) ; 
 int intel_pin_and_fence_fb_obj (struct drm_device*,struct drm_i915_gem_object*,struct intel_ring_buffer*) ; 
 int /*<<< orphan*/  intel_ring_advance (struct intel_ring_buffer*) ; 
 int intel_ring_begin (struct intel_ring_buffer*,int) ; 
 int /*<<< orphan*/  intel_ring_emit (struct intel_ring_buffer*,int) ; 
 int /*<<< orphan*/  intel_unpin_fb_obj (struct drm_i915_gem_object*) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 

__attribute__((used)) static int intel_gen4_queue_flip(struct drm_device *dev,
				 struct drm_crtc *crtc,
				 struct drm_framebuffer *fb,
				 struct drm_i915_gem_object *obj)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	uint32_t pf, pipesrc;
	struct intel_ring_buffer *ring = &dev_priv->ring[RCS];
	int ret;

	ret = intel_pin_and_fence_fb_obj(dev, obj, ring);
	if (ret)
		goto err;

	ret = intel_ring_begin(ring, 4);
	if (ret)
		goto err_unpin;

	/* i965+ uses the linear or tiled offsets from the
	 * Display Registers (which do not change across a page-flip)
	 * so we need only reprogram the base address.
	 */
	intel_ring_emit(ring, MI_DISPLAY_FLIP |
			MI_DISPLAY_FLIP_PLANE(intel_crtc->plane));
	intel_ring_emit(ring, fb->pitches[0]);
	intel_ring_emit(ring,
			(obj->gtt_offset + intel_crtc->dspaddr_offset) |
			obj->tiling_mode);

	/* XXX Enabling the panel-fitter across page-flip is so far
	 * untested on non-native modes, so ignore it for now.
	 * pf = I915_READ(pipe == 0 ? PFA_CTL_1 : PFB_CTL_1) & PF_ENABLE;
	 */
	pf = 0;
	pipesrc = I915_READ(PIPESRC(intel_crtc->pipe)) & 0x0fff0fff;
	intel_ring_emit(ring, pf | pipesrc);

	intel_mark_page_flip_active(intel_crtc);
	intel_ring_advance(ring);
	return 0;

err_unpin:
	intel_unpin_fb_obj(obj);
err:
	return ret;
}