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
struct drm_device {scalar_t__ dev_private; } ;
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;
typedef  int /*<<< orphan*/  drm_i915_private_t ;
struct TYPE_2__ {int gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ) ; 
 int DRM_SCANOUTPOS_ACCURATE ; 
 int DRM_SCANOUTPOS_INVBL ; 
 int DRM_SCANOUTPOS_VALID ; 
 int /*<<< orphan*/  HTOTAL (int) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 TYPE_1__* INTEL_INFO (struct drm_device*) ; 
 int /*<<< orphan*/  PIPEDSL (int) ; 
 int /*<<< orphan*/  PIPEFRAMEPIXEL (int) ; 
 int PIPE_PIXEL_MASK ; 
 int PIPE_PIXEL_SHIFT ; 
 int /*<<< orphan*/  VBLANK (int) ; 
 int /*<<< orphan*/  VTOTAL (int) ; 
 int /*<<< orphan*/  i915_pipe_enabled (struct drm_device*,int) ; 
 int intel_pipe_to_cpu_transcoder (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pipe_name (int) ; 

__attribute__((used)) static int i915_get_crtc_scanoutpos(struct drm_device *dev, int pipe,
			     int *vpos, int *hpos)
{
	drm_i915_private_t *dev_priv = (drm_i915_private_t *) dev->dev_private;
	u32 vbl = 0, position = 0;
	int vbl_start, vbl_end, htotal, vtotal;
	bool in_vbl = true;
	int ret = 0;
	enum transcoder cpu_transcoder = intel_pipe_to_cpu_transcoder(dev_priv,
								      pipe);

	if (!i915_pipe_enabled(dev, pipe)) {
		DRM_DEBUG_DRIVER("trying to get scanoutpos for disabled "
				 "pipe %c\n", pipe_name(pipe));
		return 0;
	}

	/* Get vtotal. */
	vtotal = 1 + ((I915_READ(VTOTAL(cpu_transcoder)) >> 16) & 0x1fff);

	if (INTEL_INFO(dev)->gen >= 4) {
		/* No obvious pixelcount register. Only query vertical
		 * scanout position from Display scan line register.
		 */
		position = I915_READ(PIPEDSL(pipe));

		/* Decode into vertical scanout position. Don't have
		 * horizontal scanout position.
		 */
		*vpos = position & 0x1fff;
		*hpos = 0;
	} else {
		/* Have access to pixelcount since start of frame.
		 * We can split this into vertical and horizontal
		 * scanout position.
		 */
		position = (I915_READ(PIPEFRAMEPIXEL(pipe)) & PIPE_PIXEL_MASK) >> PIPE_PIXEL_SHIFT;

		htotal = 1 + ((I915_READ(HTOTAL(cpu_transcoder)) >> 16) & 0x1fff);
		*vpos = position / htotal;
		*hpos = position - (*vpos * htotal);
	}

	/* Query vblank area. */
	vbl = I915_READ(VBLANK(cpu_transcoder));

	/* Test position against vblank region. */
	vbl_start = vbl & 0x1fff;
	vbl_end = (vbl >> 16) & 0x1fff;

	if ((*vpos < vbl_start) || (*vpos > vbl_end))
		in_vbl = false;

	/* Inside "upper part" of vblank area? Apply corrective offset: */
	if (in_vbl && (*vpos >= vbl_start))
		*vpos = *vpos - vtotal;

	/* Readouts valid? */
	if (vbl > 0)
		ret |= DRM_SCANOUTPOS_VALID | DRM_SCANOUTPOS_ACCURATE;

	/* In vblank? */
	if (in_vbl)
		ret |= DRM_SCANOUTPOS_INVBL;

	return ret;
}