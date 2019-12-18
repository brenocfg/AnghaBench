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
 scalar_t__ IS_ERR_OR_NULL (struct edid*) ; 
 int drm_add_edid_modes (struct drm_connector*,struct edid*) ; 
 char* drm_get_connector_name (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_mode_connector_update_edid_property (struct drm_connector*,struct edid*) ; 
 char* edid_firmware ; 
 scalar_t__ edid_load (struct drm_connector*,char*,char*) ; 
 int /*<<< orphan*/  kfree (struct edid*) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

int drm_load_edid_firmware(struct drm_connector *connector)
{
	char *connector_name = drm_get_connector_name(connector);
	char *edidname = edid_firmware, *last, *colon;
	int ret;
	struct edid *edid;

	if (*edidname == '\0')
		return 0;

	colon = strchr(edidname, ':');
	if (colon != NULL) {
		if (strncmp(connector_name, edidname, colon - edidname))
			return 0;
		edidname = colon + 1;
		if (*edidname == '\0')
			return 0;
	}

	last = edidname + strlen(edidname) - 1;
	if (*last == '\n')
		*last = '\0';

	edid = (struct edid *) edid_load(connector, edidname, connector_name);
	if (IS_ERR_OR_NULL(edid))
		return 0;

	drm_mode_connector_update_edid_property(connector, edid);
	ret = drm_add_edid_modes(connector, edid);
	kfree(edid);

	return ret;
}