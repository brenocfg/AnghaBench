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
struct radeon_device {scalar_t__ family; } ;
struct drm_display_mode {int hdisplay; int vdisplay; int crtc_htotal; int crtc_hdisplay; int crtc_hsync_end; int crtc_hsync_start; int flags; int crtc_vtotal; int crtc_vdisplay; int crtc_vsync_end; int crtc_vsync_start; int crtc_hblank_end; int crtc_hblank_start; int crtc_vblank_end; int crtc_vblank_start; } ;
struct radeon_crtc {int rmx_type; struct drm_display_mode native_mode; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;
typedef  int scale ;
typedef  int blank_width ;

/* Variables and functions */
 scalar_t__ CHIP_RS100 ; 
 scalar_t__ CHIP_RS200 ; 
 int DRM_MODE_FLAG_NHSYNC ; 
 int DRM_MODE_FLAG_NVSYNC ; 
 int RADEON_CRTC_AUTO_HORZ_CENTER_EN ; 
 int RADEON_CRTC_AUTO_VERT_CENTER_EN ; 
 int RADEON_CRTC_H_CUTOFF_ACTIVE_EN ; 
 int RADEON_CRTC_H_SYNC_POL ; 
 int /*<<< orphan*/  RADEON_CRTC_MORE_CNTL ; 
 int RADEON_CRTC_V_SYNC_POL ; 
 int /*<<< orphan*/  RADEON_FP_CRTC_H_TOTAL_DISP ; 
 int /*<<< orphan*/  RADEON_FP_CRTC_V_TOTAL_DISP ; 
 int /*<<< orphan*/  RADEON_FP_HORZ_STRETCH ; 
 int /*<<< orphan*/  RADEON_FP_HORZ_VERT_ACTIVE ; 
 int /*<<< orphan*/  RADEON_FP_H_SYNC_STRT_WID ; 
 int /*<<< orphan*/  RADEON_FP_VERT_STRETCH ; 
 int /*<<< orphan*/  RADEON_FP_V_SYNC_STRT_WID ; 
 int RADEON_HORZ_AUTO_RATIO_INC ; 
 int RADEON_HORZ_FP_LOOP_STRETCH ; 
 int RADEON_HORZ_STRETCH_BLEND ; 
 int RADEON_HORZ_STRETCH_ENABLE ; 
 int /*<<< orphan*/  RADEON_HORZ_STRETCH_RATIO_MASK ; 
 int RADEON_HORZ_STRETCH_RATIO_MAX ; 
 int RADEON_VERT_AUTO_RATIO_INC ; 
 int RADEON_VERT_STRETCH_BLEND ; 
 int RADEON_VERT_STRETCH_ENABLE ; 
 int /*<<< orphan*/  RADEON_VERT_STRETCH_RATIO_MASK ; 
 int RADEON_VERT_STRETCH_RATIO_MAX ; 
 int RADEON_VERT_STRETCH_RESERVED ; 
#define  RMX_ASPECT 131 
#define  RMX_CENTER 130 
#define  RMX_FULL 129 
#define  RMX_OFF 128 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 struct radeon_crtc* to_radeon_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void radeon_legacy_rmx_mode_set(struct drm_crtc *crtc,
				       struct drm_display_mode *mode)
{
	struct drm_device *dev = crtc->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	int xres = mode->hdisplay;
	int yres = mode->vdisplay;
	bool hscale = true, vscale = true;
	int hsync_wid;
	int vsync_wid;
	int hsync_start;
	int blank_width;
	u32 scale, inc, crtc_more_cntl;
	u32 fp_horz_stretch, fp_vert_stretch, fp_horz_vert_active;
	u32 fp_h_sync_strt_wid, fp_crtc_h_total_disp;
	u32 fp_v_sync_strt_wid, fp_crtc_v_total_disp;
	struct drm_display_mode *native_mode = &radeon_crtc->native_mode;

	fp_vert_stretch = RREG32(RADEON_FP_VERT_STRETCH) &
		(RADEON_VERT_STRETCH_RESERVED |
		 RADEON_VERT_AUTO_RATIO_INC);
	fp_horz_stretch = RREG32(RADEON_FP_HORZ_STRETCH) &
		(RADEON_HORZ_FP_LOOP_STRETCH |
		 RADEON_HORZ_AUTO_RATIO_INC);

	crtc_more_cntl = 0;
	if ((rdev->family == CHIP_RS100) ||
	    (rdev->family == CHIP_RS200)) {
		/* This is to workaround the asic bug for RMX, some versions
		   of BIOS dosen't have this register initialized correctly. */
		crtc_more_cntl |= RADEON_CRTC_H_CUTOFF_ACTIVE_EN;
	}


	fp_crtc_h_total_disp = ((((mode->crtc_htotal / 8) - 1) & 0x3ff)
				| ((((mode->crtc_hdisplay / 8) - 1) & 0x1ff) << 16));

	hsync_wid = (mode->crtc_hsync_end - mode->crtc_hsync_start) / 8;
	if (!hsync_wid)
		hsync_wid = 1;
	hsync_start = mode->crtc_hsync_start - 8;

	fp_h_sync_strt_wid = ((hsync_start & 0x1fff)
			      | ((hsync_wid & 0x3f) << 16)
			      | ((mode->flags & DRM_MODE_FLAG_NHSYNC)
				 ? RADEON_CRTC_H_SYNC_POL
				 : 0));

	fp_crtc_v_total_disp = (((mode->crtc_vtotal - 1) & 0xffff)
				| ((mode->crtc_vdisplay - 1) << 16));

	vsync_wid = mode->crtc_vsync_end - mode->crtc_vsync_start;
	if (!vsync_wid)
		vsync_wid = 1;

	fp_v_sync_strt_wid = (((mode->crtc_vsync_start - 1) & 0xfff)
			      | ((vsync_wid & 0x1f) << 16)
			      | ((mode->flags & DRM_MODE_FLAG_NVSYNC)
				 ? RADEON_CRTC_V_SYNC_POL
				 : 0));

	fp_horz_vert_active = 0;

	if (native_mode->hdisplay == 0 ||
	    native_mode->vdisplay == 0) {
		hscale = false;
		vscale = false;
	} else {
		if (xres > native_mode->hdisplay)
			xres = native_mode->hdisplay;
		if (yres > native_mode->vdisplay)
			yres = native_mode->vdisplay;

		if (xres == native_mode->hdisplay)
			hscale = false;
		if (yres == native_mode->vdisplay)
			vscale = false;
	}

	switch (radeon_crtc->rmx_type) {
	case RMX_FULL:
	case RMX_ASPECT:
		if (!hscale)
			fp_horz_stretch |= ((xres/8-1) << 16);
		else {
			inc = (fp_horz_stretch & RADEON_HORZ_AUTO_RATIO_INC) ? 1 : 0;
			scale = ((xres + inc) * RADEON_HORZ_STRETCH_RATIO_MAX)
				/ native_mode->hdisplay + 1;
			fp_horz_stretch |= (((scale) & RADEON_HORZ_STRETCH_RATIO_MASK) |
					RADEON_HORZ_STRETCH_BLEND |
					RADEON_HORZ_STRETCH_ENABLE |
					((native_mode->hdisplay/8-1) << 16));
		}

		if (!vscale)
			fp_vert_stretch |= ((yres-1) << 12);
		else {
			inc = (fp_vert_stretch & RADEON_VERT_AUTO_RATIO_INC) ? 1 : 0;
			scale = ((yres + inc) * RADEON_VERT_STRETCH_RATIO_MAX)
				/ native_mode->vdisplay + 1;
			fp_vert_stretch |= (((scale) & RADEON_VERT_STRETCH_RATIO_MASK) |
					RADEON_VERT_STRETCH_ENABLE |
					RADEON_VERT_STRETCH_BLEND |
					((native_mode->vdisplay-1) << 12));
		}
		break;
	case RMX_CENTER:
		fp_horz_stretch |= ((xres/8-1) << 16);
		fp_vert_stretch |= ((yres-1) << 12);

		crtc_more_cntl |= (RADEON_CRTC_AUTO_HORZ_CENTER_EN |
				RADEON_CRTC_AUTO_VERT_CENTER_EN);

		blank_width = (mode->crtc_hblank_end - mode->crtc_hblank_start) / 8;
		if (blank_width > 110)
			blank_width = 110;

		fp_crtc_h_total_disp = (((blank_width) & 0x3ff)
				| ((((mode->crtc_hdisplay / 8) - 1) & 0x1ff) << 16));

		hsync_wid = (mode->crtc_hsync_end - mode->crtc_hsync_start) / 8;
		if (!hsync_wid)
			hsync_wid = 1;

		fp_h_sync_strt_wid = ((((mode->crtc_hsync_start - mode->crtc_hblank_start) / 8) & 0x1fff)
				| ((hsync_wid & 0x3f) << 16)
				| ((mode->flags & DRM_MODE_FLAG_NHSYNC)
					? RADEON_CRTC_H_SYNC_POL
					: 0));

		fp_crtc_v_total_disp = (((mode->crtc_vblank_end - mode->crtc_vblank_start) & 0xffff)
				| ((mode->crtc_vdisplay - 1) << 16));

		vsync_wid = mode->crtc_vsync_end - mode->crtc_vsync_start;
		if (!vsync_wid)
			vsync_wid = 1;

		fp_v_sync_strt_wid = ((((mode->crtc_vsync_start - mode->crtc_vblank_start) & 0xfff)
					| ((vsync_wid & 0x1f) << 16)
					| ((mode->flags & DRM_MODE_FLAG_NVSYNC)
						? RADEON_CRTC_V_SYNC_POL
						: 0)));

		fp_horz_vert_active = (((native_mode->vdisplay) & 0xfff) |
				(((native_mode->hdisplay / 8) & 0x1ff) << 16));
		break;
	case RMX_OFF:
	default:
		fp_horz_stretch |= ((xres/8-1) << 16);
		fp_vert_stretch |= ((yres-1) << 12);
		break;
	}

	WREG32(RADEON_FP_HORZ_STRETCH,      fp_horz_stretch);
	WREG32(RADEON_FP_VERT_STRETCH,      fp_vert_stretch);
	WREG32(RADEON_CRTC_MORE_CNTL,       crtc_more_cntl);
	WREG32(RADEON_FP_HORZ_VERT_ACTIVE,  fp_horz_vert_active);
	WREG32(RADEON_FP_H_SYNC_STRT_WID,   fp_h_sync_strt_wid);
	WREG32(RADEON_FP_V_SYNC_STRT_WID,   fp_v_sync_strt_wid);
	WREG32(RADEON_FP_CRTC_H_TOTAL_DISP, fp_crtc_h_total_disp);
	WREG32(RADEON_FP_CRTC_V_TOTAL_DISP, fp_crtc_v_total_disp);
}