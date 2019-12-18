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
struct intel_watermark_params {int guard_size; int /*<<< orphan*/  cacheline_size; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {int clock; } ;
struct drm_crtc {TYPE_1__ mode; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_crtc* intel_get_crtc_for_plane (struct drm_device*,int) ; 
 int /*<<< orphan*/  min (int,int) ; 

__attribute__((used)) static bool
sandybridge_compute_sprite_srwm(struct drm_device *dev, int plane,
				uint32_t sprite_width, int pixel_size,
				const struct intel_watermark_params *display,
				int latency_ns, int *sprite_wm)
{
	struct drm_crtc *crtc;
	unsigned long line_time_us;
	int clock;
	int line_count, line_size;
	int small, large;
	int entries;

	if (!latency_ns) {
		*sprite_wm = 0;
		return false;
	}

	crtc = intel_get_crtc_for_plane(dev, plane);
	clock = crtc->mode.clock;
	if (!clock) {
		*sprite_wm = 0;
		return false;
	}

	line_time_us = (sprite_width * 1000) / clock;
	if (!line_time_us) {
		*sprite_wm = 0;
		return false;
	}

	line_count = (latency_ns / line_time_us + 1000) / 1000;
	line_size = sprite_width * pixel_size;

	/* Use the minimum of the small and large buffer method for primary */
	small = ((clock * pixel_size / 1000) * latency_ns) / 1000;
	large = line_count * line_size;

	entries = DIV_ROUND_UP(min(small, large), display->cacheline_size);
	*sprite_wm = entries + display->guard_size;

	return *sprite_wm > 0x3ff ? false : true;
}