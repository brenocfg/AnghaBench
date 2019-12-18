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
typedef  int /*<<< orphan*/  u8 ;
struct edid {int revision; int input; } ;

/* Variables and functions */
 int DRM_EDID_INPUT_DIGITAL ; 
 int /*<<< orphan*/  drm_for_each_detailed_block (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  is_rb ; 

__attribute__((used)) static bool
drm_monitor_supports_rb(struct edid *edid)
{
	if (edid->revision >= 4) {
		bool ret = false;
		drm_for_each_detailed_block((u8 *)edid, is_rb, &ret);
		return ret;
	}

	return ((edid->input & DRM_EDID_INPUT_DIGITAL) != 0);
}