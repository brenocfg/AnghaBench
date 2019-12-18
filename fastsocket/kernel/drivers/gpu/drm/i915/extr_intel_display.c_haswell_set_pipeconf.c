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
struct intel_crtc {int cpu_transcoder; } ;
struct drm_i915_private {int dummy; } ;
struct drm_display_mode {int flags; } ;
struct drm_crtc {TYPE_1__* dev; } ;
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;
struct TYPE_2__ {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_INTERLACE ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PIPECONF (int) ; 
 int PIPECONF_DITHER_EN ; 
 int PIPECONF_DITHER_TYPE_MASK ; 
 int PIPECONF_DITHER_TYPE_SP ; 
 int PIPECONF_INTERLACED_ILK ; 
 int PIPECONF_INTERLACE_MASK_HSW ; 
 int PIPECONF_PROGRESSIVE ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void haswell_set_pipeconf(struct drm_crtc *crtc,
				 struct drm_display_mode *adjusted_mode,
				 bool dither)
{
	struct drm_i915_private *dev_priv = crtc->dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	enum transcoder cpu_transcoder = intel_crtc->cpu_transcoder;
	uint32_t val;

	val = I915_READ(PIPECONF(cpu_transcoder));

	val &= ~(PIPECONF_DITHER_EN | PIPECONF_DITHER_TYPE_MASK);
	if (dither)
		val |= (PIPECONF_DITHER_EN | PIPECONF_DITHER_TYPE_SP);

	val &= ~PIPECONF_INTERLACE_MASK_HSW;
	if (adjusted_mode->flags & DRM_MODE_FLAG_INTERLACE)
		val |= PIPECONF_INTERLACED_ILK;
	else
		val |= PIPECONF_PROGRESSIVE;

	I915_WRITE(PIPECONF(cpu_transcoder), val);
	POSTING_READ(PIPECONF(cpu_transcoder));
}