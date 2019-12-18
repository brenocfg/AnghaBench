#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct nv17_tv_encoder {int overscan; } ;
struct nv04_crtc_reg {int* fp_horiz_regs; int* fp_vert_regs; int fp_debug_1; } ;
struct drm_encoder {TYPE_5__* crtc; struct drm_device* dev; } ;
struct drm_display_mode {int flags; int hdisplay; int vdisplay; } ;
struct drm_device {int dummy; } ;
struct TYPE_8__ {struct drm_display_mode mode; } ;
struct TYPE_12__ {TYPE_2__ ctv_enc_mode; } ;
struct TYPE_11__ {struct drm_display_mode mode; } ;
struct TYPE_10__ {int index; } ;
struct TYPE_7__ {struct nv04_crtc_reg* crtc_reg; } ;
struct TYPE_9__ {TYPE_1__ mode_reg; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_INTERLACE ; 
 size_t FP_VALID_END ; 
 size_t FP_VALID_START ; 
 int /*<<< orphan*/  NVWriteRAMDAC (struct drm_device*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NV_PRAMDAC_FP_DEBUG_1 ; 
 int NV_PRAMDAC_FP_DEBUG_1_XSCALE_TESTMODE_ENABLE ; 
 int /*<<< orphan*/  NV_PRAMDAC_FP_DEBUG_1_XSCALE_VALUE ; 
 int NV_PRAMDAC_FP_DEBUG_1_YSCALE_TESTMODE_ENABLE ; 
 int /*<<< orphan*/  NV_PRAMDAC_FP_DEBUG_1_YSCALE_VALUE ; 
 int /*<<< orphan*/  NV_PRAMDAC_FP_HVALID_END ; 
 int /*<<< orphan*/  NV_PRAMDAC_FP_HVALID_START ; 
 int /*<<< orphan*/  NV_PRAMDAC_FP_VVALID_END ; 
 int /*<<< orphan*/  NV_PRAMDAC_FP_VVALID_START ; 
 int XLATE (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* get_tv_norm (struct drm_encoder*) ; 
 int interpolate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  min (int,int) ; 
 TYPE_4__* nouveau_crtc (TYPE_5__*) ; 
 TYPE_3__* nv04_display (struct drm_device*) ; 
 struct nv17_tv_encoder* to_tv_enc (struct drm_encoder*) ; 

void nv17_ctv_update_rescaler(struct drm_encoder *encoder)
{
	struct drm_device *dev = encoder->dev;
	struct nv17_tv_encoder *tv_enc = to_tv_enc(encoder);
	int head = nouveau_crtc(encoder->crtc)->index;
	struct nv04_crtc_reg *regs = &nv04_display(dev)->mode_reg.crtc_reg[head];
	struct drm_display_mode *crtc_mode = &encoder->crtc->mode;
	struct drm_display_mode *output_mode =
		&get_tv_norm(encoder)->ctv_enc_mode.mode;
	int overscan, hmargin, vmargin, hratio, vratio;

	/* The rescaler doesn't do the right thing for interlaced modes. */
	if (output_mode->flags & DRM_MODE_FLAG_INTERLACE)
		overscan = 100;
	else
		overscan = tv_enc->overscan;

	hmargin = (output_mode->hdisplay - crtc_mode->hdisplay) / 2;
	vmargin = (output_mode->vdisplay - crtc_mode->vdisplay) / 2;

	hmargin = interpolate(0, min(hmargin, output_mode->hdisplay/20),
			      hmargin, overscan);
	vmargin = interpolate(0, min(vmargin, output_mode->vdisplay/20),
			      vmargin, overscan);

	hratio = crtc_mode->hdisplay * 0x800 /
		(output_mode->hdisplay - 2*hmargin);
	vratio = crtc_mode->vdisplay * 0x800 /
		(output_mode->vdisplay - 2*vmargin) & ~3;

	regs->fp_horiz_regs[FP_VALID_START] = hmargin;
	regs->fp_horiz_regs[FP_VALID_END] = output_mode->hdisplay - hmargin - 1;
	regs->fp_vert_regs[FP_VALID_START] = vmargin;
	regs->fp_vert_regs[FP_VALID_END] = output_mode->vdisplay - vmargin - 1;

	regs->fp_debug_1 = NV_PRAMDAC_FP_DEBUG_1_YSCALE_TESTMODE_ENABLE |
		XLATE(vratio, 0, NV_PRAMDAC_FP_DEBUG_1_YSCALE_VALUE) |
		NV_PRAMDAC_FP_DEBUG_1_XSCALE_TESTMODE_ENABLE |
		XLATE(hratio, 0, NV_PRAMDAC_FP_DEBUG_1_XSCALE_VALUE);

	NVWriteRAMDAC(dev, head, NV_PRAMDAC_FP_HVALID_START,
		      regs->fp_horiz_regs[FP_VALID_START]);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_FP_HVALID_END,
		      regs->fp_horiz_regs[FP_VALID_END]);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_FP_VVALID_START,
		      regs->fp_vert_regs[FP_VALID_START]);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_FP_VVALID_END,
		      regs->fp_vert_regs[FP_VALID_END]);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_FP_DEBUG_1, regs->fp_debug_1);
}