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
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
typedef  int u32 ;
struct radeon_framebuffer {struct drm_gem_object* obj; } ;
struct radeon_device {scalar_t__ family; } ;
struct radeon_crtc {scalar_t__ crtc_id; scalar_t__ crtc_offset; } ;
struct radeon_bo {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct drm_framebuffer {int bits_per_pixel; int width; int height; int* pitches; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct TYPE_2__ {int hdisplay; int vdisplay; } ;
struct drm_crtc {struct drm_framebuffer* fb; TYPE_1__ mode; struct drm_device* dev; } ;

/* Variables and functions */
 scalar_t__ AVIVO_D1GRPH_CONTROL ; 
 int AVIVO_D1GRPH_CONTROL_16BPP_ARGB1555 ; 
 int AVIVO_D1GRPH_CONTROL_16BPP_RGB565 ; 
 int AVIVO_D1GRPH_CONTROL_32BPP_ARGB8888 ; 
 int AVIVO_D1GRPH_CONTROL_8BPP_INDEXED ; 
 int AVIVO_D1GRPH_CONTROL_DEPTH_16BPP ; 
 int AVIVO_D1GRPH_CONTROL_DEPTH_32BPP ; 
 int AVIVO_D1GRPH_CONTROL_DEPTH_8BPP ; 
 scalar_t__ AVIVO_D1GRPH_ENABLE ; 
 scalar_t__ AVIVO_D1GRPH_FLIP_CONTROL ; 
 int AVIVO_D1GRPH_MACRO_ADDRESS_MODE ; 
 scalar_t__ AVIVO_D1GRPH_PITCH ; 
 scalar_t__ AVIVO_D1GRPH_PRIMARY_SURFACE_ADDRESS ; 
 scalar_t__ AVIVO_D1GRPH_SECONDARY_SURFACE_ADDRESS ; 
 scalar_t__ AVIVO_D1GRPH_SURFACE_OFFSET_X ; 
 scalar_t__ AVIVO_D1GRPH_SURFACE_OFFSET_Y ; 
 int AVIVO_D1GRPH_SURFACE_UPDATE_H_RETRACE_EN ; 
 int AVIVO_D1GRPH_TILED ; 
 scalar_t__ AVIVO_D1GRPH_X_END ; 
 scalar_t__ AVIVO_D1GRPH_X_START ; 
 scalar_t__ AVIVO_D1GRPH_Y_END ; 
 scalar_t__ AVIVO_D1GRPH_Y_START ; 
 scalar_t__ AVIVO_D1MODE_DESKTOP_HEIGHT ; 
 scalar_t__ AVIVO_D1MODE_MASTER_UPDATE_MODE ; 
 scalar_t__ AVIVO_D1MODE_VIEWPORT_SIZE ; 
 scalar_t__ AVIVO_D1MODE_VIEWPORT_START ; 
 scalar_t__ AVIVO_D1VGA_CONTROL ; 
 scalar_t__ AVIVO_D2VGA_CONTROL ; 
 scalar_t__ CHIP_R600 ; 
 scalar_t__ CHIP_RV770 ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int EINVAL ; 
 int R600_D1GRPH_ARRAY_MODE_1D_TILED_THIN1 ; 
 int R600_D1GRPH_ARRAY_MODE_2D_TILED_THIN1 ; 
 scalar_t__ R600_D1GRPH_SWAP_CONTROL ; 
 int R600_D1GRPH_SWAP_ENDIAN_16BIT ; 
 int R600_D1GRPH_SWAP_ENDIAN_32BIT ; 
 int R600_D1GRPH_SWAP_ENDIAN_NONE ; 
 scalar_t__ R700_D1GRPH_PRIMARY_SURFACE_ADDRESS_HIGH ; 
 scalar_t__ R700_D1GRPH_SECONDARY_SURFACE_ADDRESS_HIGH ; 
 scalar_t__ R700_D2GRPH_PRIMARY_SURFACE_ADDRESS_HIGH ; 
 scalar_t__ R700_D2GRPH_SECONDARY_SURFACE_ADDRESS_HIGH ; 
 int /*<<< orphan*/  RADEON_GEM_DOMAIN_VRAM ; 
 int RADEON_TILING_MACRO ; 
 int RADEON_TILING_MICRO ; 
 int RREG32 (scalar_t__) ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 struct radeon_bo* gem_to_radeon_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  radeon_bandwidth_update (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_bo_get_tiling_flags (struct radeon_bo*,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ radeon_bo_gpu_offset (struct radeon_bo*) ; 
 int radeon_bo_pin (struct radeon_bo*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int radeon_bo_reserve (struct radeon_bo*,int) ; 
 int /*<<< orphan*/  radeon_bo_unpin (struct radeon_bo*) ; 
 int /*<<< orphan*/  radeon_bo_unreserve (struct radeon_bo*) ; 
 struct radeon_crtc* to_radeon_crtc (struct drm_crtc*) ; 
 struct radeon_framebuffer* to_radeon_framebuffer (struct drm_framebuffer*) ; 
 scalar_t__ unlikely (int) ; 
 int upper_32_bits (scalar_t__) ; 

__attribute__((used)) static int avivo_crtc_do_set_base(struct drm_crtc *crtc,
				  struct drm_framebuffer *fb,
				  int x, int y, int atomic)
{
	struct radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	struct drm_device *dev = crtc->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_framebuffer *radeon_fb;
	struct drm_gem_object *obj;
	struct radeon_bo *rbo;
	struct drm_framebuffer *target_fb;
	uint64_t fb_location;
	uint32_t fb_format, fb_pitch_pixels, tiling_flags;
	u32 fb_swap = R600_D1GRPH_SWAP_ENDIAN_NONE;
	u32 tmp, viewport_w, viewport_h;
	int r;

	/* no fb bound */
	if (!atomic && !crtc->fb) {
		DRM_DEBUG_KMS("No FB bound\n");
		return 0;
	}

	if (atomic) {
		radeon_fb = to_radeon_framebuffer(fb);
		target_fb = fb;
	}
	else {
		radeon_fb = to_radeon_framebuffer(crtc->fb);
		target_fb = crtc->fb;
	}

	obj = radeon_fb->obj;
	rbo = gem_to_radeon_bo(obj);
	r = radeon_bo_reserve(rbo, false);
	if (unlikely(r != 0))
		return r;

	/* If atomic, assume fb object is pinned & idle & fenced and
	 * just update base pointers
	 */
	if (atomic)
		fb_location = radeon_bo_gpu_offset(rbo);
	else {
		r = radeon_bo_pin(rbo, RADEON_GEM_DOMAIN_VRAM, &fb_location);
		if (unlikely(r != 0)) {
			radeon_bo_unreserve(rbo);
			return -EINVAL;
		}
	}
	radeon_bo_get_tiling_flags(rbo, &tiling_flags, NULL);
	radeon_bo_unreserve(rbo);

	switch (target_fb->bits_per_pixel) {
	case 8:
		fb_format =
		    AVIVO_D1GRPH_CONTROL_DEPTH_8BPP |
		    AVIVO_D1GRPH_CONTROL_8BPP_INDEXED;
		break;
	case 15:
		fb_format =
		    AVIVO_D1GRPH_CONTROL_DEPTH_16BPP |
		    AVIVO_D1GRPH_CONTROL_16BPP_ARGB1555;
		break;
	case 16:
		fb_format =
		    AVIVO_D1GRPH_CONTROL_DEPTH_16BPP |
		    AVIVO_D1GRPH_CONTROL_16BPP_RGB565;
#ifdef __BIG_ENDIAN
		fb_swap = R600_D1GRPH_SWAP_ENDIAN_16BIT;
#endif
		break;
	case 24:
	case 32:
		fb_format =
		    AVIVO_D1GRPH_CONTROL_DEPTH_32BPP |
		    AVIVO_D1GRPH_CONTROL_32BPP_ARGB8888;
#ifdef __BIG_ENDIAN
		fb_swap = R600_D1GRPH_SWAP_ENDIAN_32BIT;
#endif
		break;
	default:
		DRM_ERROR("Unsupported screen depth %d\n",
			  target_fb->bits_per_pixel);
		return -EINVAL;
	}

	if (rdev->family >= CHIP_R600) {
		if (tiling_flags & RADEON_TILING_MACRO)
			fb_format |= R600_D1GRPH_ARRAY_MODE_2D_TILED_THIN1;
		else if (tiling_flags & RADEON_TILING_MICRO)
			fb_format |= R600_D1GRPH_ARRAY_MODE_1D_TILED_THIN1;
	} else {
		if (tiling_flags & RADEON_TILING_MACRO)
			fb_format |= AVIVO_D1GRPH_MACRO_ADDRESS_MODE;

		if (tiling_flags & RADEON_TILING_MICRO)
			fb_format |= AVIVO_D1GRPH_TILED;
	}

	if (radeon_crtc->crtc_id == 0)
		WREG32(AVIVO_D1VGA_CONTROL, 0);
	else
		WREG32(AVIVO_D2VGA_CONTROL, 0);

	if (rdev->family >= CHIP_RV770) {
		if (radeon_crtc->crtc_id) {
			WREG32(R700_D2GRPH_PRIMARY_SURFACE_ADDRESS_HIGH, upper_32_bits(fb_location));
			WREG32(R700_D2GRPH_SECONDARY_SURFACE_ADDRESS_HIGH, upper_32_bits(fb_location));
		} else {
			WREG32(R700_D1GRPH_PRIMARY_SURFACE_ADDRESS_HIGH, upper_32_bits(fb_location));
			WREG32(R700_D1GRPH_SECONDARY_SURFACE_ADDRESS_HIGH, upper_32_bits(fb_location));
		}
	}
	WREG32(AVIVO_D1GRPH_PRIMARY_SURFACE_ADDRESS + radeon_crtc->crtc_offset,
	       (u32) fb_location);
	WREG32(AVIVO_D1GRPH_SECONDARY_SURFACE_ADDRESS +
	       radeon_crtc->crtc_offset, (u32) fb_location);
	WREG32(AVIVO_D1GRPH_CONTROL + radeon_crtc->crtc_offset, fb_format);
	if (rdev->family >= CHIP_R600)
		WREG32(R600_D1GRPH_SWAP_CONTROL + radeon_crtc->crtc_offset, fb_swap);

	WREG32(AVIVO_D1GRPH_SURFACE_OFFSET_X + radeon_crtc->crtc_offset, 0);
	WREG32(AVIVO_D1GRPH_SURFACE_OFFSET_Y + radeon_crtc->crtc_offset, 0);
	WREG32(AVIVO_D1GRPH_X_START + radeon_crtc->crtc_offset, 0);
	WREG32(AVIVO_D1GRPH_Y_START + radeon_crtc->crtc_offset, 0);
	WREG32(AVIVO_D1GRPH_X_END + radeon_crtc->crtc_offset, target_fb->width);
	WREG32(AVIVO_D1GRPH_Y_END + radeon_crtc->crtc_offset, target_fb->height);

	fb_pitch_pixels = target_fb->pitches[0] / (target_fb->bits_per_pixel / 8);
	WREG32(AVIVO_D1GRPH_PITCH + radeon_crtc->crtc_offset, fb_pitch_pixels);
	WREG32(AVIVO_D1GRPH_ENABLE + radeon_crtc->crtc_offset, 1);

	WREG32(AVIVO_D1MODE_DESKTOP_HEIGHT + radeon_crtc->crtc_offset,
	       target_fb->height);
	x &= ~3;
	y &= ~1;
	WREG32(AVIVO_D1MODE_VIEWPORT_START + radeon_crtc->crtc_offset,
	       (x << 16) | y);
	viewport_w = crtc->mode.hdisplay;
	viewport_h = (crtc->mode.vdisplay + 1) & ~1;
	WREG32(AVIVO_D1MODE_VIEWPORT_SIZE + radeon_crtc->crtc_offset,
	       (viewport_w << 16) | viewport_h);

	/* pageflip setup */
	/* make sure flip is at vb rather than hb */
	tmp = RREG32(AVIVO_D1GRPH_FLIP_CONTROL + radeon_crtc->crtc_offset);
	tmp &= ~AVIVO_D1GRPH_SURFACE_UPDATE_H_RETRACE_EN;
	WREG32(AVIVO_D1GRPH_FLIP_CONTROL + radeon_crtc->crtc_offset, tmp);

	/* set pageflip to happen anywhere in vblank interval */
	WREG32(AVIVO_D1MODE_MASTER_UPDATE_MODE + radeon_crtc->crtc_offset, 0);

	if (!atomic && fb && fb != crtc->fb) {
		radeon_fb = to_radeon_framebuffer(fb);
		rbo = gem_to_radeon_bo(radeon_fb->obj);
		r = radeon_bo_reserve(rbo, false);
		if (unlikely(r != 0))
			return r;
		radeon_bo_unpin(rbo);
		radeon_bo_unreserve(rbo);
	}

	/* Bytes per pixel may have changed */
	radeon_bandwidth_update(rdev);

	return 0;
}