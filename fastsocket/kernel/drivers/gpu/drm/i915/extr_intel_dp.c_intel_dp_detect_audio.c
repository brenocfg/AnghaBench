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
struct intel_dp {int /*<<< orphan*/  adapter; } ;
struct edid {int dummy; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int drm_detect_monitor_audio (struct edid*) ; 
 struct intel_dp* intel_attached_dp (struct drm_connector*) ; 
 struct edid* intel_dp_get_edid (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct edid*) ; 

__attribute__((used)) static bool
intel_dp_detect_audio(struct drm_connector *connector)
{
	struct intel_dp *intel_dp = intel_attached_dp(connector);
	struct edid *edid;
	bool has_audio = false;

	edid = intel_dp_get_edid(connector, &intel_dp->adapter);
	if (edid) {
		has_audio = drm_detect_monitor_audio(edid);
		kfree(edid);
	}

	return has_audio;
}