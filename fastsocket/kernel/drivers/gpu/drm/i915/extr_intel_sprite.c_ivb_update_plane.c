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
struct intel_plane {int pipe; scalar_t__ can_scale; } ;
struct drm_plane {struct drm_device* dev; } ;
struct drm_i915_private {int sprite_scaling_enabled; } ;
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
 int /*<<< orphan*/  I915_MODIFY_DISPBASE (int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned int I915_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ I915_TILING_NONE ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ IS_HASWELL (struct drm_device*) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPRCTL (int) ; 
 unsigned int SPRITE_ENABLE ; 
 unsigned int SPRITE_FORMAT_RGBX888 ; 
 unsigned int SPRITE_FORMAT_YUV422 ; 
 unsigned int SPRITE_PIPE_CSC_ENABLE ; 
 unsigned int SPRITE_PIXFORMAT_MASK ; 
 unsigned int SPRITE_RGB_ORDER_RGBX ; 
 unsigned int SPRITE_SCALE_ENABLE ; 
 unsigned int SPRITE_TILED ; 
 unsigned int SPRITE_TRICKLE_FEED_DISABLE ; 
 unsigned int SPRITE_YUV_BYTE_ORDER_MASK ; 
 unsigned int SPRITE_YUV_ORDER_UYVY ; 
 unsigned int SPRITE_YUV_ORDER_VYUY ; 
 unsigned int SPRITE_YUV_ORDER_YUYV ; 
 unsigned int SPRITE_YUV_ORDER_YVYU ; 
 int /*<<< orphan*/  SPRLINOFF (int) ; 
 int /*<<< orphan*/  SPROFFSET (int) ; 
 int /*<<< orphan*/  SPRPOS (int) ; 
 int /*<<< orphan*/  SPRSCALE (int) ; 
 int /*<<< orphan*/  SPRSIZE (int) ; 
 int /*<<< orphan*/  SPRSTRIDE (int) ; 
 int /*<<< orphan*/  SPRSURF (int) ; 
 int /*<<< orphan*/  SPRTILEOFF (int) ; 
 int drm_format_plane_cpp (int,int /*<<< orphan*/ ) ; 
 unsigned long intel_gen4_compute_page_offset (unsigned int*,unsigned int*,scalar_t__,int,unsigned int) ; 
 int /*<<< orphan*/  intel_update_sprite_watermarks (struct drm_device*,int,unsigned int,int) ; 
 int /*<<< orphan*/  intel_update_watermarks (struct drm_device*) ; 
 int /*<<< orphan*/  intel_wait_for_vblank (struct drm_device*,int) ; 
 struct intel_plane* to_intel_plane (struct drm_plane*) ; 

__attribute__((used)) static void
ivb_update_plane(struct drm_plane *plane, struct drm_framebuffer *fb,
		 struct drm_i915_gem_object *obj, int crtc_x, int crtc_y,
		 unsigned int crtc_w, unsigned int crtc_h,
		 uint32_t x, uint32_t y,
		 uint32_t src_w, uint32_t src_h)
{
	struct drm_device *dev = plane->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_plane *intel_plane = to_intel_plane(plane);
	int pipe = intel_plane->pipe;
	u32 sprctl, sprscale = 0;
	unsigned long sprsurf_offset, linear_offset;
	int pixel_size = drm_format_plane_cpp(fb->pixel_format, 0);
	bool scaling_was_enabled = dev_priv->sprite_scaling_enabled;

	sprctl = I915_READ(SPRCTL(pipe));

	/* Mask out pixel format bits in case we change it */
	sprctl &= ~SPRITE_PIXFORMAT_MASK;
	sprctl &= ~SPRITE_RGB_ORDER_RGBX;
	sprctl &= ~SPRITE_YUV_BYTE_ORDER_MASK;
	sprctl &= ~SPRITE_TILED;

	switch (fb->pixel_format) {
	case DRM_FORMAT_XBGR8888:
		sprctl |= SPRITE_FORMAT_RGBX888 | SPRITE_RGB_ORDER_RGBX;
		break;
	case DRM_FORMAT_XRGB8888:
		sprctl |= SPRITE_FORMAT_RGBX888;
		break;
	case DRM_FORMAT_YUYV:
		sprctl |= SPRITE_FORMAT_YUV422 | SPRITE_YUV_ORDER_YUYV;
		break;
	case DRM_FORMAT_YVYU:
		sprctl |= SPRITE_FORMAT_YUV422 | SPRITE_YUV_ORDER_YVYU;
		break;
	case DRM_FORMAT_UYVY:
		sprctl |= SPRITE_FORMAT_YUV422 | SPRITE_YUV_ORDER_UYVY;
		break;
	case DRM_FORMAT_VYUY:
		sprctl |= SPRITE_FORMAT_YUV422 | SPRITE_YUV_ORDER_VYUY;
		break;
	default:
		BUG();
	}

	if (obj->tiling_mode != I915_TILING_NONE)
		sprctl |= SPRITE_TILED;

	/* must disable */
	sprctl |= SPRITE_TRICKLE_FEED_DISABLE;
	sprctl |= SPRITE_ENABLE;

	if (IS_HASWELL(dev))
		sprctl |= SPRITE_PIPE_CSC_ENABLE;

	/* Sizes are 0 based */
	src_w--;
	src_h--;
	crtc_w--;
	crtc_h--;

	intel_update_sprite_watermarks(dev, pipe, crtc_w, pixel_size);

	/*
	 * IVB workaround: must disable low power watermarks for at least
	 * one frame before enabling scaling.  LP watermarks can be re-enabled
	 * when scaling is disabled.
	 */
	if (crtc_w != src_w || crtc_h != src_h) {
		dev_priv->sprite_scaling_enabled |= 1 << pipe;

		if (!scaling_was_enabled) {
			intel_update_watermarks(dev);
			intel_wait_for_vblank(dev, pipe);
		}
		sprscale = SPRITE_SCALE_ENABLE | (src_w << 16) | src_h;
	} else
		dev_priv->sprite_scaling_enabled &= ~(1 << pipe);

	I915_WRITE(SPRSTRIDE(pipe), fb->pitches[0]);
	I915_WRITE(SPRPOS(pipe), (crtc_y << 16) | crtc_x);

	linear_offset = y * fb->pitches[0] + x * pixel_size;
	sprsurf_offset =
		intel_gen4_compute_page_offset(&x, &y, obj->tiling_mode,
					       pixel_size, fb->pitches[0]);
	linear_offset -= sprsurf_offset;

	/* HSW consolidates SPRTILEOFF and SPRLINOFF into a single SPROFFSET
	 * register */
	if (IS_HASWELL(dev))
		I915_WRITE(SPROFFSET(pipe), (y << 16) | x);
	else if (obj->tiling_mode != I915_TILING_NONE)
		I915_WRITE(SPRTILEOFF(pipe), (y << 16) | x);
	else
		I915_WRITE(SPRLINOFF(pipe), linear_offset);

	I915_WRITE(SPRSIZE(pipe), (crtc_h << 16) | crtc_w);
	if (intel_plane->can_scale)
		I915_WRITE(SPRSCALE(pipe), sprscale);
	I915_WRITE(SPRCTL(pipe), sprctl);
	I915_MODIFY_DISPBASE(SPRSURF(pipe), obj->gtt_offset + sprsurf_offset);
	POSTING_READ(SPRSURF(pipe));

	/* potentially re-enable LP watermarks */
	if (scaling_was_enabled && !dev_priv->sprite_scaling_enabled)
		intel_update_watermarks(dev);
}