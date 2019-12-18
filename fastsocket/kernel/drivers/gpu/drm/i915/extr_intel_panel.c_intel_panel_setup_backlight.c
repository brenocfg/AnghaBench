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
struct drm_connector {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_panel_init_backlight (int /*<<< orphan*/ ) ; 

int intel_panel_setup_backlight(struct drm_connector *connector)
{
	intel_panel_init_backlight(connector->dev);
	return 0;
}