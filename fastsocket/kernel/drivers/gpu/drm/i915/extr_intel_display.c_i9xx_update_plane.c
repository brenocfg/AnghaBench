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
typedef  unsigned long u32 ;
struct intel_framebuffer {struct drm_i915_gem_object* obj; } ;
struct intel_crtc {int plane; unsigned long dspaddr_offset; } ;
struct drm_i915_private {int dummy; } ;
struct drm_i915_gem_object {scalar_t__ tiling_mode; unsigned long gtt_offset; } ;
struct drm_framebuffer {int pixel_format; int* pitches; int bits_per_pixel; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;
struct TYPE_2__ {int gen; } ;

/* Variables and functions */
 unsigned long DISPPLANE_8BPP ; 
 unsigned long DISPPLANE_BGRX101010 ; 
 unsigned long DISPPLANE_BGRX555 ; 
 unsigned long DISPPLANE_BGRX565 ; 
 unsigned long DISPPLANE_BGRX888 ; 
 unsigned long DISPPLANE_PIXFORMAT_MASK ; 
 unsigned long DISPPLANE_RGBX101010 ; 
 unsigned long DISPPLANE_RGBX888 ; 
 unsigned long DISPPLANE_TILED ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,unsigned long,unsigned long,int,int,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
#define  DRM_FORMAT_ABGR2101010 139 
#define  DRM_FORMAT_ABGR8888 138 
#define  DRM_FORMAT_ARGB1555 137 
#define  DRM_FORMAT_ARGB2101010 136 
#define  DRM_FORMAT_ARGB8888 135 
#define  DRM_FORMAT_C8 134 
#define  DRM_FORMAT_RGB565 133 
#define  DRM_FORMAT_XBGR2101010 132 
#define  DRM_FORMAT_XBGR8888 131 
#define  DRM_FORMAT_XRGB1555 130 
#define  DRM_FORMAT_XRGB2101010 129 
#define  DRM_FORMAT_XRGB8888 128 
 unsigned long DSPADDR (int) ; 
 unsigned long DSPCNTR (int) ; 
 unsigned long DSPLINOFF (int) ; 
 unsigned long DSPSTRIDE (int) ; 
 int /*<<< orphan*/  DSPSURF (int) ; 
 unsigned long DSPTILEOFF (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  I915_MODIFY_DISPBASE (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long I915_READ (unsigned long) ; 
 scalar_t__ I915_TILING_NONE ; 
 int /*<<< orphan*/  I915_WRITE (unsigned long,unsigned long) ; 
 TYPE_1__* INTEL_INFO (struct drm_device*) ; 
 int /*<<< orphan*/  POSTING_READ (unsigned long) ; 
 unsigned long intel_gen4_compute_page_offset (int*,int*,scalar_t__,int,int) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 
 struct intel_framebuffer* to_intel_framebuffer (struct drm_framebuffer*) ; 

__attribute__((used)) static int i9xx_update_plane(struct drm_crtc *crtc, struct drm_framebuffer *fb,
			     int x, int y)
{
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	struct intel_framebuffer *intel_fb;
	struct drm_i915_gem_object *obj;
	int plane = intel_crtc->plane;
	unsigned long linear_offset;
	u32 dspcntr;
	u32 reg;

	switch (plane) {
	case 0:
	case 1:
		break;
	default:
		DRM_ERROR("Can't update plane %d in SAREA\n", plane);
		return -EINVAL;
	}

	intel_fb = to_intel_framebuffer(fb);
	obj = intel_fb->obj;

	reg = DSPCNTR(plane);
	dspcntr = I915_READ(reg);
	/* Mask out pixel format bits in case we change it */
	dspcntr &= ~DISPPLANE_PIXFORMAT_MASK;
	switch (fb->pixel_format) {
	case DRM_FORMAT_C8:
		dspcntr |= DISPPLANE_8BPP;
		break;
	case DRM_FORMAT_XRGB1555:
	case DRM_FORMAT_ARGB1555:
		dspcntr |= DISPPLANE_BGRX555;
		break;
	case DRM_FORMAT_RGB565:
		dspcntr |= DISPPLANE_BGRX565;
		break;
	case DRM_FORMAT_XRGB8888:
	case DRM_FORMAT_ARGB8888:
		dspcntr |= DISPPLANE_BGRX888;
		break;
	case DRM_FORMAT_XBGR8888:
	case DRM_FORMAT_ABGR8888:
		dspcntr |= DISPPLANE_RGBX888;
		break;
	case DRM_FORMAT_XRGB2101010:
	case DRM_FORMAT_ARGB2101010:
		dspcntr |= DISPPLANE_BGRX101010;
		break;
	case DRM_FORMAT_XBGR2101010:
	case DRM_FORMAT_ABGR2101010:
		dspcntr |= DISPPLANE_RGBX101010;
		break;
	default:
		DRM_ERROR("Unknown pixel format 0x%08x\n", fb->pixel_format);
		return -EINVAL;
	}

	if (INTEL_INFO(dev)->gen >= 4) {
		if (obj->tiling_mode != I915_TILING_NONE)
			dspcntr |= DISPPLANE_TILED;
		else
			dspcntr &= ~DISPPLANE_TILED;
	}

	I915_WRITE(reg, dspcntr);

	linear_offset = y * fb->pitches[0] + x * (fb->bits_per_pixel / 8);

	if (INTEL_INFO(dev)->gen >= 4) {
		intel_crtc->dspaddr_offset =
			intel_gen4_compute_page_offset(&x, &y, obj->tiling_mode,
						       fb->bits_per_pixel / 8,
						       fb->pitches[0]);
		linear_offset -= intel_crtc->dspaddr_offset;
	} else {
		intel_crtc->dspaddr_offset = linear_offset;
	}

	DRM_DEBUG_KMS("Writing base %08X %08lX %d %d %d\n",
		      obj->gtt_offset, linear_offset, x, y, fb->pitches[0]);
	I915_WRITE(DSPSTRIDE(plane), fb->pitches[0]);
	if (INTEL_INFO(dev)->gen >= 4) {
		I915_MODIFY_DISPBASE(DSPSURF(plane),
				     obj->gtt_offset + intel_crtc->dspaddr_offset);
		I915_WRITE(DSPTILEOFF(plane), (y << 16) | x);
		I915_WRITE(DSPLINOFF(plane), linear_offset);
	} else
		I915_WRITE(DSPADDR(plane), obj->gtt_offset + linear_offset);
	POSTING_READ(reg);

	return 0;
}