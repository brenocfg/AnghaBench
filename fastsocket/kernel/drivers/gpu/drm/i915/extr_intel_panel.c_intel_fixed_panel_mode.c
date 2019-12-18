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
struct drm_display_mode {int /*<<< orphan*/  clock; int /*<<< orphan*/  vtotal; int /*<<< orphan*/  vsync_end; int /*<<< orphan*/  vsync_start; int /*<<< orphan*/  vdisplay; int /*<<< orphan*/  htotal; int /*<<< orphan*/  hsync_end; int /*<<< orphan*/  hsync_start; int /*<<< orphan*/  hdisplay; } ;

/* Variables and functions */

void
intel_fixed_panel_mode(struct drm_display_mode *fixed_mode,
		       struct drm_display_mode *adjusted_mode)
{
	adjusted_mode->hdisplay = fixed_mode->hdisplay;
	adjusted_mode->hsync_start = fixed_mode->hsync_start;
	adjusted_mode->hsync_end = fixed_mode->hsync_end;
	adjusted_mode->htotal = fixed_mode->htotal;

	adjusted_mode->vdisplay = fixed_mode->vdisplay;
	adjusted_mode->vsync_start = fixed_mode->vsync_start;
	adjusted_mode->vsync_end = fixed_mode->vsync_end;
	adjusted_mode->vtotal = fixed_mode->vtotal;

	adjusted_mode->clock = fixed_mode->clock;
}