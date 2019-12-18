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
struct intel_sdvo_connector {int dummy; } ;
struct edid {int input; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int) ; 
 int DRM_EDID_INPUT_DIGITAL ; 
 int /*<<< orphan*/  IS_DIGITAL (struct intel_sdvo_connector*) ; 

__attribute__((used)) static bool
intel_sdvo_connector_matches_edid(struct intel_sdvo_connector *sdvo,
				  struct edid *edid)
{
	bool monitor_is_digital = !!(edid->input & DRM_EDID_INPUT_DIGITAL);
	bool connector_is_digital = !!IS_DIGITAL(sdvo);

	DRM_DEBUG_KMS("connector_is_digital? %d, monitor_is_digital? %d\n",
		      connector_is_digital, monitor_is_digital);
	return connector_is_digital == monitor_is_digital;
}