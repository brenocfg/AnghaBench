#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  crtc; struct drm_device* dev; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
struct intel_crt {TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;
struct TYPE_6__ {int pipe; } ;

/* Variables and functions */
 int BCLRPAT (int) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int I915_READ (int) ; 
 int I915_READ8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int,int) ; 
 int /*<<< orphan*/  IS_GEN2 (struct drm_device*) ; 
 int PIPECONF (int) ; 
 int PIPECONF_FORCE_BORDER ; 
 int PIPEDSL (int) ; 
 int /*<<< orphan*/  POSTING_READ (int) ; 
 int VBLANK (int) ; 
 int /*<<< orphan*/  VGA_MSR_WRITE ; 
 int VSYNC (int) ; 
 int VTOTAL (int) ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 int /*<<< orphan*/  intel_wait_for_vblank (struct drm_device*,int) ; 
 TYPE_3__* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum drm_connector_status
intel_crt_load_detect(struct intel_crt *crt)
{
	struct drm_device *dev = crt->base.base.dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	uint32_t pipe = to_intel_crtc(crt->base.base.crtc)->pipe;
	uint32_t save_bclrpat;
	uint32_t save_vtotal;
	uint32_t vtotal, vactive;
	uint32_t vsample;
	uint32_t vblank, vblank_start, vblank_end;
	uint32_t dsl;
	uint32_t bclrpat_reg;
	uint32_t vtotal_reg;
	uint32_t vblank_reg;
	uint32_t vsync_reg;
	uint32_t pipeconf_reg;
	uint32_t pipe_dsl_reg;
	uint8_t	st00;
	enum drm_connector_status status;

	DRM_DEBUG_KMS("starting load-detect on CRT\n");

	bclrpat_reg = BCLRPAT(pipe);
	vtotal_reg = VTOTAL(pipe);
	vblank_reg = VBLANK(pipe);
	vsync_reg = VSYNC(pipe);
	pipeconf_reg = PIPECONF(pipe);
	pipe_dsl_reg = PIPEDSL(pipe);

	save_bclrpat = I915_READ(bclrpat_reg);
	save_vtotal = I915_READ(vtotal_reg);
	vblank = I915_READ(vblank_reg);

	vtotal = ((save_vtotal >> 16) & 0xfff) + 1;
	vactive = (save_vtotal & 0x7ff) + 1;

	vblank_start = (vblank & 0xfff) + 1;
	vblank_end = ((vblank >> 16) & 0xfff) + 1;

	/* Set the border color to purple. */
	I915_WRITE(bclrpat_reg, 0x500050);

	if (!IS_GEN2(dev)) {
		uint32_t pipeconf = I915_READ(pipeconf_reg);
		I915_WRITE(pipeconf_reg, pipeconf | PIPECONF_FORCE_BORDER);
		POSTING_READ(pipeconf_reg);
		/* Wait for next Vblank to substitue
		 * border color for Color info */
		intel_wait_for_vblank(dev, pipe);
		st00 = I915_READ8(VGA_MSR_WRITE);
		status = ((st00 & (1 << 4)) != 0) ?
			connector_status_connected :
			connector_status_disconnected;

		I915_WRITE(pipeconf_reg, pipeconf);
	} else {
		bool restore_vblank = false;
		int count, detect;

		/*
		* If there isn't any border, add some.
		* Yes, this will flicker
		*/
		if (vblank_start <= vactive && vblank_end >= vtotal) {
			uint32_t vsync = I915_READ(vsync_reg);
			uint32_t vsync_start = (vsync & 0xffff) + 1;

			vblank_start = vsync_start;
			I915_WRITE(vblank_reg,
				   (vblank_start - 1) |
				   ((vblank_end - 1) << 16));
			restore_vblank = true;
		}
		/* sample in the vertical border, selecting the larger one */
		if (vblank_start - vactive >= vtotal - vblank_end)
			vsample = (vblank_start + vactive) >> 1;
		else
			vsample = (vtotal + vblank_end) >> 1;

		/*
		 * Wait for the border to be displayed
		 */
		while (I915_READ(pipe_dsl_reg) >= vactive)
			;
		while ((dsl = I915_READ(pipe_dsl_reg)) <= vsample)
			;
		/*
		 * Watch ST00 for an entire scanline
		 */
		detect = 0;
		count = 0;
		do {
			count++;
			/* Read the ST00 VGA status register */
			st00 = I915_READ8(VGA_MSR_WRITE);
			if (st00 & (1 << 4))
				detect++;
		} while ((I915_READ(pipe_dsl_reg) == dsl));

		/* restore vblank if necessary */
		if (restore_vblank)
			I915_WRITE(vblank_reg, vblank);
		/*
		 * If more than 3/4 of the scanline detected a monitor,
		 * then it is assumed to be present. This works even on i830,
		 * where there isn't any way to force the border color across
		 * the screen
		 */
		status = detect * 4 > count * 3 ?
			 connector_status_connected :
			 connector_status_disconnected;
	}

	/* Restore previous settings */
	I915_WRITE(bclrpat_reg, save_bclrpat);

	return status;
}