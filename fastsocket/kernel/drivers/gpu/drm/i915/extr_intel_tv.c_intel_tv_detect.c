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
struct intel_tv {int type; } ;
struct intel_load_detect_pipe {int dummy; } ;
struct drm_display_mode {int dummy; } ;
struct drm_connector {int status; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 int connector_status_unknown ; 
 struct intel_tv* intel_attached_tv (struct drm_connector*) ; 
 scalar_t__ intel_get_load_detect_pipe (struct drm_connector*,struct drm_display_mode*,struct intel_load_detect_pipe*) ; 
 int /*<<< orphan*/  intel_release_load_detect_pipe (struct drm_connector*,struct intel_load_detect_pipe*) ; 
 int intel_tv_detect_type (struct intel_tv*,struct drm_connector*) ; 
 int /*<<< orphan*/  intel_tv_find_better_format (struct drm_connector*) ; 
 struct drm_display_mode* reported_modes ; 

__attribute__((used)) static enum drm_connector_status
intel_tv_detect(struct drm_connector *connector, bool force)
{
	struct drm_display_mode mode;
	struct intel_tv *intel_tv = intel_attached_tv(connector);
	int type;

	mode = reported_modes[0];

	if (force) {
		struct intel_load_detect_pipe tmp;

		if (intel_get_load_detect_pipe(connector, &mode, &tmp)) {
			type = intel_tv_detect_type(intel_tv, connector);
			intel_release_load_detect_pipe(connector, &tmp);
		} else
			return connector_status_unknown;
	} else
		return connector->status;

	if (type < 0)
		return connector_status_disconnected;

	intel_tv->type = type;
	intel_tv_find_better_format(connector);

	return connector_status_connected;
}