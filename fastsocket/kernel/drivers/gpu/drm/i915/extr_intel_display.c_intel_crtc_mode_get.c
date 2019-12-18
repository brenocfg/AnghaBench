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
struct intel_crtc {int cpu_transcoder; } ;
struct drm_i915_private {int dummy; } ;
struct drm_display_mode {int hdisplay; int htotal; int hsync_start; int hsync_end; int vdisplay; int vtotal; int vsync_start; int vsync_end; int /*<<< orphan*/  clock; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct drm_crtc {int dummy; } ;
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HSYNC (int) ; 
 int /*<<< orphan*/  HTOTAL (int) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VSYNC (int) ; 
 int /*<<< orphan*/  VTOTAL (int) ; 
 int /*<<< orphan*/  drm_mode_set_name (struct drm_display_mode*) ; 
 int /*<<< orphan*/  intel_crtc_clock_get (struct drm_device*,struct drm_crtc*) ; 
 struct drm_display_mode* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 

struct drm_display_mode *intel_crtc_mode_get(struct drm_device *dev,
					     struct drm_crtc *crtc)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	enum transcoder cpu_transcoder = intel_crtc->cpu_transcoder;
	struct drm_display_mode *mode;
	int htot = I915_READ(HTOTAL(cpu_transcoder));
	int hsync = I915_READ(HSYNC(cpu_transcoder));
	int vtot = I915_READ(VTOTAL(cpu_transcoder));
	int vsync = I915_READ(VSYNC(cpu_transcoder));

	mode = kzalloc(sizeof(*mode), GFP_KERNEL);
	if (!mode)
		return NULL;

	mode->clock = intel_crtc_clock_get(dev, crtc);
	mode->hdisplay = (htot & 0xffff) + 1;
	mode->htotal = ((htot & 0xffff0000) >> 16) + 1;
	mode->hsync_start = (hsync & 0xffff) + 1;
	mode->hsync_end = ((hsync & 0xffff0000) >> 16) + 1;
	mode->vdisplay = (vtot & 0xffff) + 1;
	mode->vtotal = ((vtot & 0xffff0000) >> 16) + 1;
	mode->vsync_start = (vsync & 0xffff) + 1;
	mode->vsync_end = ((vsync & 0xffff0000) >> 16) + 1;

	drm_mode_set_name(mode);

	return mode;
}