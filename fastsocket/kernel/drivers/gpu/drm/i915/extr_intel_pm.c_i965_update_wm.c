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
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct TYPE_4__ {int clock; int htotal; int hdisplay; } ;
struct drm_crtc {TYPE_2__* fb; TYPE_1__ mode; } ;
struct TYPE_6__ {int fifo_size; int guard_size; int max_wm; int /*<<< orphan*/  cacheline_size; } ;
struct TYPE_5__ {int bits_per_pixel; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,...) ; 
 int /*<<< orphan*/  DSPFW1 ; 
 int /*<<< orphan*/  DSPFW2 ; 
 int /*<<< orphan*/  DSPFW3 ; 
 int DSPFW_CURSOR_SR_SHIFT ; 
 int DSPFW_SR_SHIFT ; 
 int /*<<< orphan*/  FW_BLC_SELF ; 
 int FW_BLC_SELF_EN ; 
 int /*<<< orphan*/  I915_FIFO_LINE_SIZE ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int I965_FIFO_SIZE ; 
 scalar_t__ IS_CRESTLINE (struct drm_device*) ; 
 TYPE_3__ i965_cursor_wm_info ; 
 struct drm_crtc* single_enabled_crtc (struct drm_device*) ; 

__attribute__((used)) static void i965_update_wm(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct drm_crtc *crtc;
	int srwm = 1;
	int cursor_sr = 16;

	/* Calc sr entries for one plane configs */
	crtc = single_enabled_crtc(dev);
	if (crtc) {
		/* self-refresh has much higher latency */
		static const int sr_latency_ns = 12000;
		int clock = crtc->mode.clock;
		int htotal = crtc->mode.htotal;
		int hdisplay = crtc->mode.hdisplay;
		int pixel_size = crtc->fb->bits_per_pixel / 8;
		unsigned long line_time_us;
		int entries;

		line_time_us = ((htotal * 1000) / clock);

		/* Use ns/us then divide to preserve precision */
		entries = (((sr_latency_ns / line_time_us) + 1000) / 1000) *
			pixel_size * hdisplay;
		entries = DIV_ROUND_UP(entries, I915_FIFO_LINE_SIZE);
		srwm = I965_FIFO_SIZE - entries;
		if (srwm < 0)
			srwm = 1;
		srwm &= 0x1ff;
		DRM_DEBUG_KMS("self-refresh entries: %d, wm: %d\n",
			      entries, srwm);

		entries = (((sr_latency_ns / line_time_us) + 1000) / 1000) *
			pixel_size * 64;
		entries = DIV_ROUND_UP(entries,
					  i965_cursor_wm_info.cacheline_size);
		cursor_sr = i965_cursor_wm_info.fifo_size -
			(entries + i965_cursor_wm_info.guard_size);

		if (cursor_sr > i965_cursor_wm_info.max_wm)
			cursor_sr = i965_cursor_wm_info.max_wm;

		DRM_DEBUG_KMS("self-refresh watermark: display plane %d "
			      "cursor %d\n", srwm, cursor_sr);

		if (IS_CRESTLINE(dev))
			I915_WRITE(FW_BLC_SELF, FW_BLC_SELF_EN);
	} else {
		/* Turn off self refresh if both pipes are enabled */
		if (IS_CRESTLINE(dev))
			I915_WRITE(FW_BLC_SELF, I915_READ(FW_BLC_SELF)
				   & ~FW_BLC_SELF_EN);
	}

	DRM_DEBUG_KMS("Setting FIFO watermarks - A: 8, B: 8, C: 8, SR %d\n",
		      srwm);

	/* 965 has limitations... */
	I915_WRITE(DSPFW1, (srwm << DSPFW_SR_SHIFT) |
		   (8 << 16) | (8 << 8) | (8 << 0));
	I915_WRITE(DSPFW2, (8 << 8) | (8 << 0));
	/* update cursor SR watermark */
	I915_WRITE(DSPFW3, (cursor_sr << DSPFW_CURSOR_SR_SHIFT));
}