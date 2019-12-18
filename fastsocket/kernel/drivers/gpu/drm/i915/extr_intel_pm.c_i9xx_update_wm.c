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
typedef  int uint32_t ;
struct intel_watermark_params {int guard_size; int fifo_size; int /*<<< orphan*/  cacheline_size; } ;
struct TYPE_4__ {int (* get_fifo_size ) (struct drm_device*,int) ;} ;
struct drm_i915_private {TYPE_1__ display; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct TYPE_5__ {int clock; int htotal; int hdisplay; } ;
struct drm_crtc {TYPE_3__* fb; TYPE_2__ mode; } ;
struct TYPE_6__ {int bits_per_pixel; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int /*<<< orphan*/  FW_BLC ; 
 int /*<<< orphan*/  FW_BLC2 ; 
 int /*<<< orphan*/  FW_BLC_SELF ; 
 int FW_BLC_SELF_EN ; 
 int FW_BLC_SELF_EN_MASK ; 
 int FW_BLC_SELF_FIFO_MASK ; 
 scalar_t__ HAS_FW_BLC (struct drm_device*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  INSTPM ; 
 int INSTPM_SELF_EN ; 
 scalar_t__ IS_GEN2 (struct drm_device*) ; 
 scalar_t__ IS_I915GM (struct drm_device*) ; 
 scalar_t__ IS_I945G (struct drm_device*) ; 
 scalar_t__ IS_I945GM (struct drm_device*) ; 
 struct intel_watermark_params i855_wm_info ; 
 struct intel_watermark_params i915_wm_info ; 
 struct intel_watermark_params i945_wm_info ; 
 int intel_calculate_wm (int,struct intel_watermark_params const*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_crtc_active (struct drm_crtc*) ; 
 struct drm_crtc* intel_get_crtc_for_plane (struct drm_device*,int) ; 
 int /*<<< orphan*/  latency_ns ; 
 int stub1 (struct drm_device*,int) ; 
 int stub2 (struct drm_device*,int) ; 

__attribute__((used)) static void i9xx_update_wm(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	const struct intel_watermark_params *wm_info;
	uint32_t fwater_lo;
	uint32_t fwater_hi;
	int cwm, srwm = 1;
	int fifo_size;
	int planea_wm, planeb_wm;
	struct drm_crtc *crtc, *enabled = NULL;

	if (IS_I945GM(dev))
		wm_info = &i945_wm_info;
	else if (!IS_GEN2(dev))
		wm_info = &i915_wm_info;
	else
		wm_info = &i855_wm_info;

	fifo_size = dev_priv->display.get_fifo_size(dev, 0);
	crtc = intel_get_crtc_for_plane(dev, 0);
	if (intel_crtc_active(crtc)) {
		int cpp = crtc->fb->bits_per_pixel / 8;
		if (IS_GEN2(dev))
			cpp = 4;

		planea_wm = intel_calculate_wm(crtc->mode.clock,
					       wm_info, fifo_size, cpp,
					       latency_ns);
		enabled = crtc;
	} else
		planea_wm = fifo_size - wm_info->guard_size;

	fifo_size = dev_priv->display.get_fifo_size(dev, 1);
	crtc = intel_get_crtc_for_plane(dev, 1);
	if (intel_crtc_active(crtc)) {
		int cpp = crtc->fb->bits_per_pixel / 8;
		if (IS_GEN2(dev))
			cpp = 4;

		planeb_wm = intel_calculate_wm(crtc->mode.clock,
					       wm_info, fifo_size, cpp,
					       latency_ns);
		if (enabled == NULL)
			enabled = crtc;
		else
			enabled = NULL;
	} else
		planeb_wm = fifo_size - wm_info->guard_size;

	DRM_DEBUG_KMS("FIFO watermarks - A: %d, B: %d\n", planea_wm, planeb_wm);

	/*
	 * Overlay gets an aggressive default since video jitter is bad.
	 */
	cwm = 2;

	/* Play safe and disable self-refresh before adjusting watermarks. */
	if (IS_I945G(dev) || IS_I945GM(dev))
		I915_WRITE(FW_BLC_SELF, FW_BLC_SELF_EN_MASK | 0);
	else if (IS_I915GM(dev))
		I915_WRITE(INSTPM, I915_READ(INSTPM) & ~INSTPM_SELF_EN);

	/* Calc sr entries for one plane configs */
	if (HAS_FW_BLC(dev) && enabled) {
		/* self-refresh has much higher latency */
		static const int sr_latency_ns = 6000;
		int clock = enabled->mode.clock;
		int htotal = enabled->mode.htotal;
		int hdisplay = enabled->mode.hdisplay;
		int pixel_size = enabled->fb->bits_per_pixel / 8;
		unsigned long line_time_us;
		int entries;

		line_time_us = (htotal * 1000) / clock;

		/* Use ns/us then divide to preserve precision */
		entries = (((sr_latency_ns / line_time_us) + 1000) / 1000) *
			pixel_size * hdisplay;
		entries = DIV_ROUND_UP(entries, wm_info->cacheline_size);
		DRM_DEBUG_KMS("self-refresh entries: %d\n", entries);
		srwm = wm_info->fifo_size - entries;
		if (srwm < 0)
			srwm = 1;

		if (IS_I945G(dev) || IS_I945GM(dev))
			I915_WRITE(FW_BLC_SELF,
				   FW_BLC_SELF_FIFO_MASK | (srwm & 0xff));
		else if (IS_I915GM(dev))
			I915_WRITE(FW_BLC_SELF, srwm & 0x3f);
	}

	DRM_DEBUG_KMS("Setting FIFO watermarks - A: %d, B: %d, C: %d, SR %d\n",
		      planea_wm, planeb_wm, cwm, srwm);

	fwater_lo = ((planeb_wm & 0x3f) << 16) | (planea_wm & 0x3f);
	fwater_hi = (cwm & 0x1f);

	/* Set request length to 8 cachelines per fetch */
	fwater_lo = fwater_lo | (1 << 24) | (1 << 8);
	fwater_hi = fwater_hi | (1 << 8);

	I915_WRITE(FW_BLC, fwater_lo);
	I915_WRITE(FW_BLC2, fwater_hi);

	if (HAS_FW_BLC(dev)) {
		if (enabled) {
			if (IS_I945G(dev) || IS_I945GM(dev))
				I915_WRITE(FW_BLC_SELF,
					   FW_BLC_SELF_EN_MASK | FW_BLC_SELF_EN);
			else if (IS_I915GM(dev))
				I915_WRITE(INSTPM, I915_READ(INSTPM) | INSTPM_SELF_EN);
			DRM_DEBUG_KMS("memory self refresh enabled\n");
		} else
			DRM_DEBUG_KMS("memory self refresh disabled\n");
	}
}