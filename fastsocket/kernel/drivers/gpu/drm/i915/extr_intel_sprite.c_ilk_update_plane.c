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
typedef  unsigned int uint32_t ;
typedef  unsigned int u32 ;
struct intel_plane {int pipe; } ;
struct drm_plane {struct drm_device* dev; } ;
struct drm_i915_private {int dummy; } ;
struct drm_i915_gem_object {scalar_t__ tiling_mode; scalar_t__ gtt_offset; } ;
struct drm_framebuffer {int pixel_format; unsigned int* pitches; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  DRM_FORMAT_UYVY 133 
#define  DRM_FORMAT_VYUY 132 
#define  DRM_FORMAT_XBGR8888 131 
#define  DRM_FORMAT_XRGB8888 130 
#define  DRM_FORMAT_YUYV 129 
#define  DRM_FORMAT_YVYU 128 
 int /*<<< orphan*/  DVSCNTR (int) ; 
 int /*<<< orphan*/  DVSLINOFF (int) ; 
 int /*<<< orphan*/  DVSPOS (int) ; 
 int /*<<< orphan*/  DVSSCALE (int) ; 
 int /*<<< orphan*/  DVSSIZE (int) ; 
 int /*<<< orphan*/  DVSSTRIDE (int) ; 
 int /*<<< orphan*/  DVSSURF (int) ; 
 int /*<<< orphan*/  DVSTILEOFF (int) ; 
 unsigned int DVS_ENABLE ; 
 unsigned int DVS_FORMAT_RGBX888 ; 
 unsigned int DVS_FORMAT_YUV422 ; 
 unsigned int DVS_PIXFORMAT_MASK ; 
 unsigned int DVS_RGB_ORDER_XBGR ; 
 unsigned int DVS_SCALE_ENABLE ; 
 unsigned int DVS_TILED ; 
 unsigned int DVS_TRICKLE_FEED_DISABLE ; 
 unsigned int DVS_YUV_BYTE_ORDER_MASK ; 
 unsigned int DVS_YUV_ORDER_UYVY ; 
 unsigned int DVS_YUV_ORDER_VYUY ; 
 unsigned int DVS_YUV_ORDER_YUYV ; 
 unsigned int DVS_YUV_ORDER_YVYU ; 
 int /*<<< orphan*/  I915_MODIFY_DISPBASE (int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned int I915_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ I915_TILING_NONE ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ IS_GEN5 (struct drm_device*) ; 
 scalar_t__ IS_GEN6 (struct drm_device*) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int drm_format_plane_cpp (int,int /*<<< orphan*/ ) ; 
 unsigned long intel_gen4_compute_page_offset (unsigned int*,unsigned int*,scalar_t__,int,unsigned int) ; 
 int /*<<< orphan*/  intel_update_sprite_watermarks (struct drm_device*,int,unsigned int,int) ; 
 struct intel_plane* to_intel_plane (struct drm_plane*) ; 

__attribute__((used)) static void
ilk_update_plane(struct drm_plane *plane, struct drm_framebuffer *fb,
		 struct drm_i915_gem_object *obj, int crtc_x, int crtc_y,
		 unsigned int crtc_w, unsigned int crtc_h,
		 uint32_t x, uint32_t y,
		 uint32_t src_w, uint32_t src_h)
{
	struct drm_device *dev = plane->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_plane *intel_plane = to_intel_plane(plane);
	int pipe = intel_plane->pipe;
	unsigned long dvssurf_offset, linear_offset;
	u32 dvscntr, dvsscale;
	int pixel_size = drm_format_plane_cpp(fb->pixel_format, 0);

	dvscntr = I915_READ(DVSCNTR(pipe));

	/* Mask out pixel format bits in case we change it */
	dvscntr &= ~DVS_PIXFORMAT_MASK;
	dvscntr &= ~DVS_RGB_ORDER_XBGR;
	dvscntr &= ~DVS_YUV_BYTE_ORDER_MASK;
	dvscntr &= ~DVS_TILED;

	switch (fb->pixel_format) {
	case DRM_FORMAT_XBGR8888:
		dvscntr |= DVS_FORMAT_RGBX888 | DVS_RGB_ORDER_XBGR;
		break;
	case DRM_FORMAT_XRGB8888:
		dvscntr |= DVS_FORMAT_RGBX888;
		break;
	case DRM_FORMAT_YUYV:
		dvscntr |= DVS_FORMAT_YUV422 | DVS_YUV_ORDER_YUYV;
		break;
	case DRM_FORMAT_YVYU:
		dvscntr |= DVS_FORMAT_YUV422 | DVS_YUV_ORDER_YVYU;
		break;
	case DRM_FORMAT_UYVY:
		dvscntr |= DVS_FORMAT_YUV422 | DVS_YUV_ORDER_UYVY;
		break;
	case DRM_FORMAT_VYUY:
		dvscntr |= DVS_FORMAT_YUV422 | DVS_YUV_ORDER_VYUY;
		break;
	default:
		BUG();
	}

	if (obj->tiling_mode != I915_TILING_NONE)
		dvscntr |= DVS_TILED;

	if (IS_GEN6(dev))
		dvscntr |= DVS_TRICKLE_FEED_DISABLE; /* must disable */
	dvscntr |= DVS_ENABLE;

	/* Sizes are 0 based */
	src_w--;
	src_h--;
	crtc_w--;
	crtc_h--;

	intel_update_sprite_watermarks(dev, pipe, crtc_w, pixel_size);

	dvsscale = 0;
	if (IS_GEN5(dev) || crtc_w != src_w || crtc_h != src_h)
		dvsscale = DVS_SCALE_ENABLE | (src_w << 16) | src_h;

	I915_WRITE(DVSSTRIDE(pipe), fb->pitches[0]);
	I915_WRITE(DVSPOS(pipe), (crtc_y << 16) | crtc_x);

	linear_offset = y * fb->pitches[0] + x * pixel_size;
	dvssurf_offset =
		intel_gen4_compute_page_offset(&x, &y, obj->tiling_mode,
					       pixel_size, fb->pitches[0]);
	linear_offset -= dvssurf_offset;

	if (obj->tiling_mode != I915_TILING_NONE)
		I915_WRITE(DVSTILEOFF(pipe), (y << 16) | x);
	else
		I915_WRITE(DVSLINOFF(pipe), linear_offset);

	I915_WRITE(DVSSIZE(pipe), (crtc_h << 16) | crtc_w);
	I915_WRITE(DVSSCALE(pipe), dvsscale);
	I915_WRITE(DVSCNTR(pipe), dvscntr);
	I915_MODIFY_DISPBASE(DVSSURF(pipe), obj->gtt_offset + dvssurf_offset);
	POSTING_READ(DVSSURF(pipe));
}