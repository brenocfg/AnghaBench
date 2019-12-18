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
struct intel_panel {struct drm_display_mode* fixed_mode; } ;
struct drm_display_mode {int dummy; } ;

/* Variables and functions */

int intel_panel_init(struct intel_panel *panel,
		     struct drm_display_mode *fixed_mode)
{
	panel->fixed_mode = fixed_mode;

	return 0;
}