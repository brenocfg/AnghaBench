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
struct edid {int dummy; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int drm_add_edid_modes (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  drm_edid_to_eld (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  drm_mode_connector_update_edid_property (struct drm_connector*,struct edid*) ; 

int intel_connector_update_modes(struct drm_connector *connector,
				struct edid *edid)
{
	int ret;

	drm_mode_connector_update_edid_property(connector, edid);
	ret = drm_add_edid_modes(connector, edid);
	drm_edid_to_eld(connector, edid);

	return ret;
}