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
struct intel_sdvo {int /*<<< orphan*/  is_hdmi; } ;
struct edid {int input; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int DRM_EDID_INPUT_DIGITAL ; 
 int drm_detect_monitor_audio (struct edid*) ; 
 struct intel_sdvo* intel_attached_sdvo (struct drm_connector*) ; 
 struct edid* intel_sdvo_get_edid (struct drm_connector*) ; 
 int /*<<< orphan*/  kfree (struct edid*) ; 

__attribute__((used)) static bool intel_sdvo_detect_hdmi_audio(struct drm_connector *connector)
{
	struct intel_sdvo *intel_sdvo = intel_attached_sdvo(connector);
	struct edid *edid;
	bool has_audio = false;

	if (!intel_sdvo->is_hdmi)
		return false;

	edid = intel_sdvo_get_edid(connector);
	if (edid != NULL && edid->input & DRM_EDID_INPUT_DIGITAL)
		has_audio = drm_detect_monitor_audio(edid);
	kfree(edid);

	return has_audio;
}