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
struct drm_device {struct drm_i915_private* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;

/* Variables and functions */
 int /*<<< orphan*/  HBLANK (int) ; 
 int /*<<< orphan*/  HSYNC (int) ; 
 int /*<<< orphan*/  HTOTAL (int) ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRANSCODER_A ; 
 int /*<<< orphan*/  VBLANK (int) ; 
 int /*<<< orphan*/  VSYNC (int) ; 
 int /*<<< orphan*/  VSYNCSHIFT (int) ; 
 int /*<<< orphan*/  VTOTAL (int) ; 
 int /*<<< orphan*/  _TRANS_HBLANK_A ; 
 int /*<<< orphan*/  _TRANS_HSYNC_A ; 
 int /*<<< orphan*/  _TRANS_HTOTAL_A ; 
 int /*<<< orphan*/  _TRANS_VBLANK_A ; 
 int /*<<< orphan*/  _TRANS_VSYNCSHIFT_A ; 
 int /*<<< orphan*/  _TRANS_VSYNC_A ; 
 int /*<<< orphan*/  _TRANS_VTOTAL_A ; 
 int /*<<< orphan*/  assert_transcoder_disabled (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpt_enable_pch_transcoder (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  lpt_program_iclkip (struct drm_crtc*) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void lpt_pch_enable(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	enum transcoder cpu_transcoder = intel_crtc->cpu_transcoder;

	assert_transcoder_disabled(dev_priv, TRANSCODER_A);

	lpt_program_iclkip(crtc);

	/* Set transcoder timing. */
	I915_WRITE(_TRANS_HTOTAL_A, I915_READ(HTOTAL(cpu_transcoder)));
	I915_WRITE(_TRANS_HBLANK_A, I915_READ(HBLANK(cpu_transcoder)));
	I915_WRITE(_TRANS_HSYNC_A,  I915_READ(HSYNC(cpu_transcoder)));

	I915_WRITE(_TRANS_VTOTAL_A, I915_READ(VTOTAL(cpu_transcoder)));
	I915_WRITE(_TRANS_VBLANK_A, I915_READ(VBLANK(cpu_transcoder)));
	I915_WRITE(_TRANS_VSYNC_A,  I915_READ(VSYNC(cpu_transcoder)));
	I915_WRITE(_TRANS_VSYNCSHIFT_A, I915_READ(VSYNCSHIFT(cpu_transcoder)));

	lpt_enable_pch_transcoder(dev_priv, cpu_transcoder);
}