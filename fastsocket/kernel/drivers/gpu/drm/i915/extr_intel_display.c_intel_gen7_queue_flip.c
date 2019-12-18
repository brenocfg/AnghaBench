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
struct intel_crtc {int plane; int dspaddr_offset; } ;
struct drm_i915_private {struct intel_ring_buffer* ring; } ;
struct drm_i915_gem_object {int tiling_mode; int gtt_offset; } ;
struct drm_framebuffer {int* pitches; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 size_t BCS ; 
 int ENODEV ; 
 int MI_DISPLAY_FLIP_I915 ; 
 int MI_DISPLAY_FLIP_IVB_PLANE_A ; 
 int MI_DISPLAY_FLIP_IVB_PLANE_B ; 
 int MI_DISPLAY_FLIP_IVB_PLANE_C ; 
 int MI_NOOP ; 
#define  PLANE_A 130 
#define  PLANE_B 129 
#define  PLANE_C 128 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  intel_mark_page_flip_active (struct intel_crtc*) ; 
 int intel_pin_and_fence_fb_obj (struct drm_device*,struct drm_i915_gem_object*,struct intel_ring_buffer*) ; 
 int /*<<< orphan*/  intel_ring_advance (struct intel_ring_buffer*) ; 
 int intel_ring_begin (struct intel_ring_buffer*,int) ; 
 int /*<<< orphan*/  intel_ring_emit (struct intel_ring_buffer*,int) ; 
 int /*<<< orphan*/  intel_unpin_fb_obj (struct drm_i915_gem_object*) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 

__attribute__((used)) static int intel_gen7_queue_flip(struct drm_device *dev,
				 struct drm_crtc *crtc,
				 struct drm_framebuffer *fb,
				 struct drm_i915_gem_object *obj)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	struct intel_ring_buffer *ring = &dev_priv->ring[BCS];
	uint32_t plane_bit = 0;
	int ret;

	ret = intel_pin_and_fence_fb_obj(dev, obj, ring);
	if (ret)
		goto err;

	switch(intel_crtc->plane) {
	case PLANE_A:
		plane_bit = MI_DISPLAY_FLIP_IVB_PLANE_A;
		break;
	case PLANE_B:
		plane_bit = MI_DISPLAY_FLIP_IVB_PLANE_B;
		break;
	case PLANE_C:
		plane_bit = MI_DISPLAY_FLIP_IVB_PLANE_C;
		break;
	default:
		WARN_ONCE(1, "unknown plane in flip command\n");
		ret = -ENODEV;
		goto err_unpin;
	}

	ret = intel_ring_begin(ring, 4);
	if (ret)
		goto err_unpin;

	intel_ring_emit(ring, MI_DISPLAY_FLIP_I915 | plane_bit);
	intel_ring_emit(ring, (fb->pitches[0] | obj->tiling_mode));
	intel_ring_emit(ring, obj->gtt_offset + intel_crtc->dspaddr_offset);
	intel_ring_emit(ring, (MI_NOOP));

	intel_mark_page_flip_active(intel_crtc);
	intel_ring_advance(ring);
	return 0;

err_unpin:
	intel_unpin_fb_obj(obj);
err:
	return ret;
}