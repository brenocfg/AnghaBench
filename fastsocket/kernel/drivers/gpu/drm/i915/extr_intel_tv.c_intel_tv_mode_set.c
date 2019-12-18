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
typedef  int u32 ;
struct video_levels {int burst; int black; int blank; } ;
struct tv_mode {int burst_ena; int hsync_end; int htotal; int hburst_start; int hburst_len; int hblank_start; int hblank_end; int nbr_end; int vi_end_f1; int vi_end_f2; int vsync_len; int vsync_start_f1; int vsync_start_f2; int veq_len; int veq_start_f1; int veq_start_f2; int vburst_start_f1; int vburst_end_f1; int vburst_start_f2; int vburst_end_f2; int vburst_start_f3; int vburst_end_f3; int vburst_start_f4; int vburst_end_f4; int oversample; int dda1_inc; int dda2_inc; int dda3_inc; int sc_reset; int dda2_size; int dda3_size; int* filter_table; scalar_t__ progressive; scalar_t__ pal_burst; scalar_t__ trilevel_sync; scalar_t__ veq_ena; struct color_conversion* svideo_color; struct video_levels* svideo_levels; struct color_conversion* composite_color; struct video_levels* composite_levels; } ;
struct intel_tv {int type; scalar_t__* margin; } ;
struct intel_crtc {int pipe; int /*<<< orphan*/  plane; } ;
struct drm_i915_private {int dummy; } ;
struct drm_encoder {struct drm_crtc* crtc; struct drm_device* dev; } ;
struct drm_display_mode {int dummy; } ;
struct drm_device {int pci_device; struct drm_i915_private* dev_private; } ;
struct drm_crtc {int dummy; } ;
struct color_conversion {int ry; int gy; int by; int ay; int ru; int gu; int bu; int au; int rv; int gv; int bv; int av; } ;
struct TYPE_2__ {int gen; } ;

/* Variables and functions */
 int DISPLAY_PLANE_ENABLE ; 
#define  DRM_MODE_CONNECTOR_Component 131 
#define  DRM_MODE_CONNECTOR_Composite 130 
#define  DRM_MODE_CONNECTOR_SVIDEO 129 
#define  DRM_MODE_CONNECTOR_Unknown 128 
 int DSPCNTR (int /*<<< orphan*/ ) ; 
 int I915_READ (int) ; 
 int /*<<< orphan*/  I915_WRITE (int,int) ; 
 TYPE_1__* INTEL_INFO (struct drm_device*) ; 
 scalar_t__ IS_GEN2 (struct drm_device*) ; 
 int PIPECONF (int) ; 
 int PIPECONF_ENABLE ; 
 int TV_AUTO_SCALE ; 
 int TV_BLACK_LEVEL_SHIFT ; 
 int TV_BLANK_LEVEL_SHIFT ; 
 int TV_BURST_ENA ; 
 int TV_BURST_LEVEL_SHIFT ; 
 int TV_CLR_KNOBS ; 
 int TV_CLR_LEVEL ; 
 int TV_CSC_U ; 
 int TV_CSC_U2 ; 
 int TV_CSC_V ; 
 int TV_CSC_V2 ; 
 int TV_CSC_Y ; 
 int TV_CSC_Y2 ; 
 int TV_CTL ; 
 int TV_CTL_SAVE ; 
 int TV_DAC ; 
 int TV_DAC_SAVE ; 
 int TV_ENC_C0_FIX ; 
 int TV_ENC_OUTPUT_COMPONENT ; 
 int TV_ENC_OUTPUT_COMPOSITE ; 
 int TV_ENC_OUTPUT_SVIDEO ; 
 int TV_ENC_PIPEB_SELECT ; 
 int TV_ENC_SDP_FIX ; 
 int TV_EQUAL_ENA ; 
 int TV_FILTER_CTL_1 ; 
 int TV_HBLANK_END_SHIFT ; 
 int TV_HBLANK_START_SHIFT ; 
 int TV_HBURST_LEN_SHIFT ; 
 int TV_HSYNC_END_SHIFT ; 
 int TV_HTOTAL_SHIFT ; 
 int TV_H_CHROMA_0 ; 
 int TV_H_CTL_1 ; 
 int TV_H_CTL_2 ; 
 int TV_H_CTL_3 ; 
 int TV_H_LUMA_0 ; 
 size_t TV_MARGIN_BOTTOM ; 
 size_t TV_MARGIN_LEFT ; 
 size_t TV_MARGIN_RIGHT ; 
 size_t TV_MARGIN_TOP ; 
 int TV_NBR_END_SHIFT ; 
 int TV_PAL_BURST ; 
 int TV_PROGRESSIVE ; 
 int TV_SCDDA1_INC_SHIFT ; 
 int TV_SCDDA2_INC_SHIFT ; 
 int TV_SCDDA2_SIZE_SHIFT ; 
 int TV_SCDDA3_INC_SHIFT ; 
 int TV_SCDDA3_SIZE_SHIFT ; 
 int TV_SC_CTL_1 ; 
 int TV_SC_CTL_2 ; 
 int TV_SC_CTL_3 ; 
 int TV_SC_DDA1_EN ; 
 int TV_SC_DDA2_EN ; 
 int TV_SC_DDA3_EN ; 
 int TV_TRILEVEL_SYNC ; 
 int TV_VBURST_END_F1_SHIFT ; 
 int TV_VBURST_END_F2_SHIFT ; 
 int TV_VBURST_END_F3_SHIFT ; 
 int TV_VBURST_END_F4_SHIFT ; 
 int TV_VBURST_START_F1_SHIFT ; 
 int TV_VBURST_START_F2_SHIFT ; 
 int TV_VBURST_START_F3_SHIFT ; 
 int TV_VBURST_START_F4_SHIFT ; 
 int TV_VEQ_LEN_SHIFT ; 
 int TV_VEQ_START_F1_SHIFT ; 
 int TV_VEQ_START_F2_SHIFT ; 
 int TV_VI_END_F1_SHIFT ; 
 int TV_VI_END_F2_SHIFT ; 
 int TV_VSYNC_LEN_SHIFT ; 
 int TV_VSYNC_START_F1_SHIFT ; 
 int TV_VSYNC_START_F2_SHIFT ; 
 int TV_V_CHROMA_0 ; 
 int TV_V_CTL_1 ; 
 int TV_V_CTL_2 ; 
 int TV_V_CTL_3 ; 
 int TV_V_CTL_4 ; 
 int TV_V_CTL_5 ; 
 int TV_V_CTL_6 ; 
 int TV_V_CTL_7 ; 
 int TV_V_LUMA_0 ; 
 int TV_WIN_POS ; 
 int TV_WIN_SIZE ; 
 struct video_levels component_levels ; 
 struct intel_tv* enc_to_intel_tv (struct drm_encoder*) ; 
 struct color_conversion hdtv_csc_yprpb ; 
 int /*<<< orphan*/  intel_flush_display_plane (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 struct tv_mode* intel_tv_mode_find (struct intel_tv*) ; 
 int /*<<< orphan*/  intel_wait_for_pipe_off (struct drm_device*,int) ; 
 int /*<<< orphan*/  intel_wait_for_vblank (struct drm_device*,int) ; 
 struct color_conversion sdtv_csc_yprpb ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void
intel_tv_mode_set(struct drm_encoder *encoder, struct drm_display_mode *mode,
		  struct drm_display_mode *adjusted_mode)
{
	struct drm_device *dev = encoder->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct drm_crtc *crtc = encoder->crtc;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	struct intel_tv *intel_tv = enc_to_intel_tv(encoder);
	const struct tv_mode *tv_mode = intel_tv_mode_find(intel_tv);
	u32 tv_ctl;
	u32 hctl1, hctl2, hctl3;
	u32 vctl1, vctl2, vctl3, vctl4, vctl5, vctl6, vctl7;
	u32 scctl1, scctl2, scctl3;
	int i, j;
	const struct video_levels *video_levels;
	const struct color_conversion *color_conversion;
	bool burst_ena;
	int pipe = intel_crtc->pipe;

	if (!tv_mode)
		return;	/* can't happen (mode_prepare prevents this) */

	tv_ctl = I915_READ(TV_CTL);
	tv_ctl &= TV_CTL_SAVE;

	switch (intel_tv->type) {
	default:
	case DRM_MODE_CONNECTOR_Unknown:
	case DRM_MODE_CONNECTOR_Composite:
		tv_ctl |= TV_ENC_OUTPUT_COMPOSITE;
		video_levels = tv_mode->composite_levels;
		color_conversion = tv_mode->composite_color;
		burst_ena = tv_mode->burst_ena;
		break;
	case DRM_MODE_CONNECTOR_Component:
		tv_ctl |= TV_ENC_OUTPUT_COMPONENT;
		video_levels = &component_levels;
		if (tv_mode->burst_ena)
			color_conversion = &sdtv_csc_yprpb;
		else
			color_conversion = &hdtv_csc_yprpb;
		burst_ena = false;
		break;
	case DRM_MODE_CONNECTOR_SVIDEO:
		tv_ctl |= TV_ENC_OUTPUT_SVIDEO;
		video_levels = tv_mode->svideo_levels;
		color_conversion = tv_mode->svideo_color;
		burst_ena = tv_mode->burst_ena;
		break;
	}
	hctl1 = (tv_mode->hsync_end << TV_HSYNC_END_SHIFT) |
		(tv_mode->htotal << TV_HTOTAL_SHIFT);

	hctl2 = (tv_mode->hburst_start << 16) |
		(tv_mode->hburst_len << TV_HBURST_LEN_SHIFT);

	if (burst_ena)
		hctl2 |= TV_BURST_ENA;

	hctl3 = (tv_mode->hblank_start << TV_HBLANK_START_SHIFT) |
		(tv_mode->hblank_end << TV_HBLANK_END_SHIFT);

	vctl1 = (tv_mode->nbr_end << TV_NBR_END_SHIFT) |
		(tv_mode->vi_end_f1 << TV_VI_END_F1_SHIFT) |
		(tv_mode->vi_end_f2 << TV_VI_END_F2_SHIFT);

	vctl2 = (tv_mode->vsync_len << TV_VSYNC_LEN_SHIFT) |
		(tv_mode->vsync_start_f1 << TV_VSYNC_START_F1_SHIFT) |
		(tv_mode->vsync_start_f2 << TV_VSYNC_START_F2_SHIFT);

	vctl3 = (tv_mode->veq_len << TV_VEQ_LEN_SHIFT) |
		(tv_mode->veq_start_f1 << TV_VEQ_START_F1_SHIFT) |
		(tv_mode->veq_start_f2 << TV_VEQ_START_F2_SHIFT);

	if (tv_mode->veq_ena)
		vctl3 |= TV_EQUAL_ENA;

	vctl4 = (tv_mode->vburst_start_f1 << TV_VBURST_START_F1_SHIFT) |
		(tv_mode->vburst_end_f1 << TV_VBURST_END_F1_SHIFT);

	vctl5 = (tv_mode->vburst_start_f2 << TV_VBURST_START_F2_SHIFT) |
		(tv_mode->vburst_end_f2 << TV_VBURST_END_F2_SHIFT);

	vctl6 = (tv_mode->vburst_start_f3 << TV_VBURST_START_F3_SHIFT) |
		(tv_mode->vburst_end_f3 << TV_VBURST_END_F3_SHIFT);

	vctl7 = (tv_mode->vburst_start_f4 << TV_VBURST_START_F4_SHIFT) |
		(tv_mode->vburst_end_f4 << TV_VBURST_END_F4_SHIFT);

	if (intel_crtc->pipe == 1)
		tv_ctl |= TV_ENC_PIPEB_SELECT;
	tv_ctl |= tv_mode->oversample;

	if (tv_mode->progressive)
		tv_ctl |= TV_PROGRESSIVE;
	if (tv_mode->trilevel_sync)
		tv_ctl |= TV_TRILEVEL_SYNC;
	if (tv_mode->pal_burst)
		tv_ctl |= TV_PAL_BURST;

	scctl1 = 0;
	if (tv_mode->dda1_inc)
		scctl1 |= TV_SC_DDA1_EN;
	if (tv_mode->dda2_inc)
		scctl1 |= TV_SC_DDA2_EN;
	if (tv_mode->dda3_inc)
		scctl1 |= TV_SC_DDA3_EN;
	scctl1 |= tv_mode->sc_reset;
	if (video_levels)
		scctl1 |= video_levels->burst << TV_BURST_LEVEL_SHIFT;
	scctl1 |= tv_mode->dda1_inc << TV_SCDDA1_INC_SHIFT;

	scctl2 = tv_mode->dda2_size << TV_SCDDA2_SIZE_SHIFT |
		tv_mode->dda2_inc << TV_SCDDA2_INC_SHIFT;

	scctl3 = tv_mode->dda3_size << TV_SCDDA3_SIZE_SHIFT |
		tv_mode->dda3_inc << TV_SCDDA3_INC_SHIFT;

	/* Enable two fixes for the chips that need them. */
	if (dev->pci_device < 0x2772)
		tv_ctl |= TV_ENC_C0_FIX | TV_ENC_SDP_FIX;

	I915_WRITE(TV_H_CTL_1, hctl1);
	I915_WRITE(TV_H_CTL_2, hctl2);
	I915_WRITE(TV_H_CTL_3, hctl3);
	I915_WRITE(TV_V_CTL_1, vctl1);
	I915_WRITE(TV_V_CTL_2, vctl2);
	I915_WRITE(TV_V_CTL_3, vctl3);
	I915_WRITE(TV_V_CTL_4, vctl4);
	I915_WRITE(TV_V_CTL_5, vctl5);
	I915_WRITE(TV_V_CTL_6, vctl6);
	I915_WRITE(TV_V_CTL_7, vctl7);
	I915_WRITE(TV_SC_CTL_1, scctl1);
	I915_WRITE(TV_SC_CTL_2, scctl2);
	I915_WRITE(TV_SC_CTL_3, scctl3);

	if (color_conversion) {
		I915_WRITE(TV_CSC_Y, (color_conversion->ry << 16) |
			   color_conversion->gy);
		I915_WRITE(TV_CSC_Y2, (color_conversion->by << 16) |
			   color_conversion->ay);
		I915_WRITE(TV_CSC_U, (color_conversion->ru << 16) |
			   color_conversion->gu);
		I915_WRITE(TV_CSC_U2, (color_conversion->bu << 16) |
			   color_conversion->au);
		I915_WRITE(TV_CSC_V, (color_conversion->rv << 16) |
			   color_conversion->gv);
		I915_WRITE(TV_CSC_V2, (color_conversion->bv << 16) |
			   color_conversion->av);
	}

	if (INTEL_INFO(dev)->gen >= 4)
		I915_WRITE(TV_CLR_KNOBS, 0x00404000);
	else
		I915_WRITE(TV_CLR_KNOBS, 0x00606000);

	if (video_levels)
		I915_WRITE(TV_CLR_LEVEL,
			   ((video_levels->black << TV_BLACK_LEVEL_SHIFT) |
			    (video_levels->blank << TV_BLANK_LEVEL_SHIFT)));
	{
		int pipeconf_reg = PIPECONF(pipe);
		int dspcntr_reg = DSPCNTR(intel_crtc->plane);
		int pipeconf = I915_READ(pipeconf_reg);
		int dspcntr = I915_READ(dspcntr_reg);
		int xpos = 0x0, ypos = 0x0;
		unsigned int xsize, ysize;
		/* Pipe must be off here */
		I915_WRITE(dspcntr_reg, dspcntr & ~DISPLAY_PLANE_ENABLE);
		intel_flush_display_plane(dev_priv, intel_crtc->plane);

		/* Wait for vblank for the disable to take effect */
		if (IS_GEN2(dev))
			intel_wait_for_vblank(dev, intel_crtc->pipe);

		I915_WRITE(pipeconf_reg, pipeconf & ~PIPECONF_ENABLE);
		/* Wait for vblank for the disable to take effect. */
		intel_wait_for_pipe_off(dev, intel_crtc->pipe);

		/* Filter ctl must be set before TV_WIN_SIZE */
		I915_WRITE(TV_FILTER_CTL_1, TV_AUTO_SCALE);
		xsize = tv_mode->hblank_start - tv_mode->hblank_end;
		if (tv_mode->progressive)
			ysize = tv_mode->nbr_end + 1;
		else
			ysize = 2*tv_mode->nbr_end + 1;

		xpos += intel_tv->margin[TV_MARGIN_LEFT];
		ypos += intel_tv->margin[TV_MARGIN_TOP];
		xsize -= (intel_tv->margin[TV_MARGIN_LEFT] +
			  intel_tv->margin[TV_MARGIN_RIGHT]);
		ysize -= (intel_tv->margin[TV_MARGIN_TOP] +
			  intel_tv->margin[TV_MARGIN_BOTTOM]);
		I915_WRITE(TV_WIN_POS, (xpos<<16)|ypos);
		I915_WRITE(TV_WIN_SIZE, (xsize<<16)|ysize);

		I915_WRITE(pipeconf_reg, pipeconf);
		I915_WRITE(dspcntr_reg, dspcntr);
		intel_flush_display_plane(dev_priv, intel_crtc->plane);
	}

	j = 0;
	for (i = 0; i < 60; i++)
		I915_WRITE(TV_H_LUMA_0 + (i<<2), tv_mode->filter_table[j++]);
	for (i = 0; i < 60; i++)
		I915_WRITE(TV_H_CHROMA_0 + (i<<2), tv_mode->filter_table[j++]);
	for (i = 0; i < 43; i++)
		I915_WRITE(TV_V_LUMA_0 + (i<<2), tv_mode->filter_table[j++]);
	for (i = 0; i < 43; i++)
		I915_WRITE(TV_V_CHROMA_0 + (i<<2), tv_mode->filter_table[j++]);
	I915_WRITE(TV_DAC, I915_READ(TV_DAC) & TV_DAC_SAVE);
	I915_WRITE(TV_CTL, tv_ctl);
}