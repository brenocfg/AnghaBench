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
typedef  int uint32_t ;
struct intel_crtc {int pipe; int bpp; } ;
struct drm_i915_private {int dummy; } ;
struct drm_display_mode {int flags; int private_flags; } ;
struct drm_crtc {TYPE_1__* dev; } ;
struct TYPE_2__ {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int INTEL_MODE_LIMITED_COLOR_RANGE ; 
 int /*<<< orphan*/  PIPECONF (int) ; 
 int PIPECONF_10BPC ; 
 int PIPECONF_12BPC ; 
 int PIPECONF_6BPC ; 
 int PIPECONF_8BPC ; 
 int PIPECONF_BPC_MASK ; 
 int PIPECONF_COLOR_RANGE_SELECT ; 
 int PIPECONF_DITHER_EN ; 
 int PIPECONF_DITHER_TYPE_MASK ; 
 int PIPECONF_DITHER_TYPE_SP ; 
 int PIPECONF_INTERLACED_ILK ; 
 int PIPECONF_INTERLACE_MASK ; 
 int PIPECONF_PROGRESSIVE ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void ironlake_set_pipeconf(struct drm_crtc *crtc,
				  struct drm_display_mode *adjusted_mode,
				  bool dither)
{
	struct drm_i915_private *dev_priv = crtc->dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	int pipe = intel_crtc->pipe;
	uint32_t val;

	val = I915_READ(PIPECONF(pipe));

	val &= ~PIPECONF_BPC_MASK;
	switch (intel_crtc->bpp) {
	case 18:
		val |= PIPECONF_6BPC;
		break;
	case 24:
		val |= PIPECONF_8BPC;
		break;
	case 30:
		val |= PIPECONF_10BPC;
		break;
	case 36:
		val |= PIPECONF_12BPC;
		break;
	default:
		/* Case prevented by intel_choose_pipe_bpp_dither. */
		BUG();
	}

	val &= ~(PIPECONF_DITHER_EN | PIPECONF_DITHER_TYPE_MASK);
	if (dither)
		val |= (PIPECONF_DITHER_EN | PIPECONF_DITHER_TYPE_SP);

	val &= ~PIPECONF_INTERLACE_MASK;
	if (adjusted_mode->flags & DRM_MODE_FLAG_INTERLACE)
		val |= PIPECONF_INTERLACED_ILK;
	else
		val |= PIPECONF_PROGRESSIVE;

	if (adjusted_mode->private_flags & INTEL_MODE_LIMITED_COLOR_RANGE)
		val |= PIPECONF_COLOR_RANGE_SELECT;
	else
		val &= ~PIPECONF_COLOR_RANGE_SELECT;

	I915_WRITE(PIPECONF(pipe), val);
	POSTING_READ(PIPECONF(pipe));
}