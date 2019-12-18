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
struct drm_display_mode {unsigned int htotal; unsigned int vtotal; int clock; unsigned int hdisplay; unsigned int vdisplay; } ;

/* Variables and functions */

__attribute__((used)) static unsigned radeon_mode_bandwidth(struct drm_display_mode *mode, int bytes_per_pixel)
{
	unsigned a_active, a_total, tmp;

	if (!mode->htotal || !mode->vtotal || !mode->clock) {
		return 0;
	}

	a_active = mode->hdisplay * mode->vdisplay;
	a_total = mode->htotal * mode->vtotal;
	tmp = ((mode->clock >> 10) * bytes_per_pixel * (a_active >> 10)) * 1000;
	return tmp/(a_total);
}