#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int dvo_reg; TYPE_1__* dev_ops; } ;
struct intel_dvo {TYPE_2__ dev; } ;
struct intel_crtc {int pipe; } ;
struct drm_i915_private {int dummy; } ;
struct drm_encoder {int /*<<< orphan*/  crtc; struct drm_device* dev; } ;
struct drm_display_mode {int flags; int hdisplay; int vdisplay; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* mode_set ) (TYPE_2__*,struct drm_display_mode*,struct drm_display_mode*) ;} ;

/* Variables and functions */
 int DPLL (int) ; 
 int DPLL_DVO_HIGH_SPEED ; 
 int DRM_MODE_FLAG_PHSYNC ; 
 int DRM_MODE_FLAG_PVSYNC ; 
#define  DVOA 130 
 int DVOA_SRCDIM ; 
#define  DVOB 129 
 int DVOB_SRCDIM ; 
#define  DVOC 128 
 int DVOC_SRCDIM ; 
 int DVO_BLANK_ACTIVE_HIGH ; 
 int DVO_BORDER_ENABLE ; 
 int DVO_DATA_ORDER_FP ; 
 int DVO_DATA_ORDER_GBRG ; 
 int DVO_HSYNC_ACTIVE_HIGH ; 
 int DVO_PIPE_B_SELECT ; 
 int DVO_PIPE_STALL ; 
 int DVO_PRESERVE_MASK ; 
 int DVO_SRCDIM_HORIZONTAL_SHIFT ; 
 int DVO_SRCDIM_VERTICAL_SHIFT ; 
 int DVO_VSYNC_ACTIVE_HIGH ; 
 int I915_READ (int) ; 
 int /*<<< orphan*/  I915_WRITE (int,int) ; 
 struct intel_dvo* enc_to_intel_dvo (struct drm_encoder*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,struct drm_display_mode*,struct drm_display_mode*) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_dvo_mode_set(struct drm_encoder *encoder,
			       struct drm_display_mode *mode,
			       struct drm_display_mode *adjusted_mode)
{
	struct drm_device *dev = encoder->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(encoder->crtc);
	struct intel_dvo *intel_dvo = enc_to_intel_dvo(encoder);
	int pipe = intel_crtc->pipe;
	u32 dvo_val;
	u32 dvo_reg = intel_dvo->dev.dvo_reg, dvo_srcdim_reg;
	int dpll_reg = DPLL(pipe);

	switch (dvo_reg) {
	case DVOA:
	default:
		dvo_srcdim_reg = DVOA_SRCDIM;
		break;
	case DVOB:
		dvo_srcdim_reg = DVOB_SRCDIM;
		break;
	case DVOC:
		dvo_srcdim_reg = DVOC_SRCDIM;
		break;
	}

	intel_dvo->dev.dev_ops->mode_set(&intel_dvo->dev, mode, adjusted_mode);

	/* Save the data order, since I don't know what it should be set to. */
	dvo_val = I915_READ(dvo_reg) &
		  (DVO_PRESERVE_MASK | DVO_DATA_ORDER_GBRG);
	dvo_val |= DVO_DATA_ORDER_FP | DVO_BORDER_ENABLE |
		   DVO_BLANK_ACTIVE_HIGH;

	if (pipe == 1)
		dvo_val |= DVO_PIPE_B_SELECT;
	dvo_val |= DVO_PIPE_STALL;
	if (adjusted_mode->flags & DRM_MODE_FLAG_PHSYNC)
		dvo_val |= DVO_HSYNC_ACTIVE_HIGH;
	if (adjusted_mode->flags & DRM_MODE_FLAG_PVSYNC)
		dvo_val |= DVO_VSYNC_ACTIVE_HIGH;

	I915_WRITE(dpll_reg, I915_READ(dpll_reg) | DPLL_DVO_HIGH_SPEED);

	/*I915_WRITE(DVOB_SRCDIM,
	  (adjusted_mode->hdisplay << DVO_SRCDIM_HORIZONTAL_SHIFT) |
	  (adjusted_mode->VDisplay << DVO_SRCDIM_VERTICAL_SHIFT));*/
	I915_WRITE(dvo_srcdim_reg,
		   (adjusted_mode->hdisplay << DVO_SRCDIM_HORIZONTAL_SHIFT) |
		   (adjusted_mode->vdisplay << DVO_SRCDIM_VERTICAL_SHIFT));
	/*I915_WRITE(DVOB, dvo_val);*/
	I915_WRITE(dvo_reg, dvo_val);
}