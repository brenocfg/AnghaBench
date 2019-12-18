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
struct minimode {int /*<<< orphan*/  r; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct edid {int dummy; } ;
struct drm_display_mode {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_connector {struct drm_device* dev; } ;
struct detailed_timing {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct minimode*) ; 
 struct drm_display_mode* drm_cvt_mode (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_destroy (struct drm_device*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 int drm_monitor_supports_rb (struct edid*) ; 
 struct minimode* extra_modes ; 
 int /*<<< orphan*/  fixup_mode_1366x768 (struct drm_display_mode*) ; 
 int /*<<< orphan*/  mode_in_range (struct drm_display_mode*,struct edid*,struct detailed_timing*) ; 
 int /*<<< orphan*/  valid_inferred_mode (struct drm_connector*,struct drm_display_mode*) ; 

__attribute__((used)) static int
drm_cvt_modes_for_range(struct drm_connector *connector, struct edid *edid,
			struct detailed_timing *timing)
{
	int i, modes = 0;
	struct drm_display_mode *newmode;
	struct drm_device *dev = connector->dev;
	bool rb = drm_monitor_supports_rb(edid);

	for (i = 0; i < ARRAY_SIZE(extra_modes); i++) {
		const struct minimode *m = &extra_modes[i];
		newmode = drm_cvt_mode(dev, m->w, m->h, m->r, rb, 0, 0);
		if (!newmode)
			return modes;

		fixup_mode_1366x768(newmode);
		if (!mode_in_range(newmode, edid, timing) ||
		    !valid_inferred_mode(connector, newmode)) {
			drm_mode_destroy(dev, newmode);
			continue;
		}

		drm_mode_probed_add(connector, newmode);
		modes++;
	}

	return modes;
}