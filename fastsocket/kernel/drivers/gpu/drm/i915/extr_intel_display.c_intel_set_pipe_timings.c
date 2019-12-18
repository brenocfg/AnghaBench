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
typedef  int uint32_t ;
struct TYPE_3__ {struct drm_device* dev; } ;
struct intel_crtc {int pipe; int cpu_transcoder; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
struct drm_display_mode {int flags; int crtc_vtotal; int crtc_vblank_end; int crtc_hsync_start; int crtc_htotal; int crtc_hdisplay; int crtc_hblank_start; int crtc_hblank_end; int crtc_hsync_end; int crtc_vdisplay; int crtc_vblank_start; int crtc_vsync_start; int crtc_vsync_end; int hdisplay; int vdisplay; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
struct TYPE_4__ {int gen; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_INTERLACE ; 
 int /*<<< orphan*/  HBLANK (int) ; 
 int /*<<< orphan*/  HSYNC (int) ; 
 int /*<<< orphan*/  HTOTAL (int) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* INTEL_INFO (struct drm_device*) ; 
 int /*<<< orphan*/  IS_GEN2 (struct drm_device*) ; 
 scalar_t__ IS_HASWELL (struct drm_device*) ; 
 int /*<<< orphan*/  PIPESRC (int) ; 
 int PIPE_B ; 
 int PIPE_C ; 
 int TRANSCODER_EDP ; 
 int /*<<< orphan*/  VBLANK (int) ; 
 int /*<<< orphan*/  VSYNC (int) ; 
 int /*<<< orphan*/  VSYNCSHIFT (int) ; 
 int /*<<< orphan*/  VTOTAL (int) ; 

__attribute__((used)) static void intel_set_pipe_timings(struct intel_crtc *intel_crtc,
				   struct drm_display_mode *mode,
				   struct drm_display_mode *adjusted_mode)
{
	struct drm_device *dev = intel_crtc->base.dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	enum pipe pipe = intel_crtc->pipe;
	enum transcoder cpu_transcoder = intel_crtc->cpu_transcoder;
	uint32_t vsyncshift;

	if (!IS_GEN2(dev) && adjusted_mode->flags & DRM_MODE_FLAG_INTERLACE) {
		/* the chip adds 2 halflines automatically */
		adjusted_mode->crtc_vtotal -= 1;
		adjusted_mode->crtc_vblank_end -= 1;
		vsyncshift = adjusted_mode->crtc_hsync_start
			     - adjusted_mode->crtc_htotal / 2;
	} else {
		vsyncshift = 0;
	}

	if (INTEL_INFO(dev)->gen > 3)
		I915_WRITE(VSYNCSHIFT(cpu_transcoder), vsyncshift);

	I915_WRITE(HTOTAL(cpu_transcoder),
		   (adjusted_mode->crtc_hdisplay - 1) |
		   ((adjusted_mode->crtc_htotal - 1) << 16));
	I915_WRITE(HBLANK(cpu_transcoder),
		   (adjusted_mode->crtc_hblank_start - 1) |
		   ((adjusted_mode->crtc_hblank_end - 1) << 16));
	I915_WRITE(HSYNC(cpu_transcoder),
		   (adjusted_mode->crtc_hsync_start - 1) |
		   ((adjusted_mode->crtc_hsync_end - 1) << 16));

	I915_WRITE(VTOTAL(cpu_transcoder),
		   (adjusted_mode->crtc_vdisplay - 1) |
		   ((adjusted_mode->crtc_vtotal - 1) << 16));
	I915_WRITE(VBLANK(cpu_transcoder),
		   (adjusted_mode->crtc_vblank_start - 1) |
		   ((adjusted_mode->crtc_vblank_end - 1) << 16));
	I915_WRITE(VSYNC(cpu_transcoder),
		   (adjusted_mode->crtc_vsync_start - 1) |
		   ((adjusted_mode->crtc_vsync_end - 1) << 16));

	/* Workaround: when the EDP input selection is B, the VTOTAL_B must be
	 * programmed with the VTOTAL_EDP value. Same for VTOTAL_C. This is
	 * documented on the DDI_FUNC_CTL register description, EDP Input Select
	 * bits. */
	if (IS_HASWELL(dev) && cpu_transcoder == TRANSCODER_EDP &&
	    (pipe == PIPE_B || pipe == PIPE_C))
		I915_WRITE(VTOTAL(pipe), I915_READ(VTOTAL(cpu_transcoder)));

	/* pipesrc controls the size that is scaled from, which should
	 * always be the user's requested size.
	 */
	I915_WRITE(PIPESRC(pipe),
		   ((mode->hdisplay - 1) << 16) | (mode->vdisplay - 1));
}