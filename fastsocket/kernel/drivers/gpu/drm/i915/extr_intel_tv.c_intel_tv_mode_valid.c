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
struct tv_mode {scalar_t__ refresh; } ;
struct intel_tv {int dummy; } ;
struct drm_display_mode {int dummy; } ;
struct drm_connector {int dummy; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;

/* Variables and functions */
 int MODE_CLOCK_RANGE ; 
 int MODE_OK ; 
 int abs (scalar_t__) ; 
 int drm_mode_vrefresh (struct drm_display_mode*) ; 
 struct intel_tv* intel_attached_tv (struct drm_connector*) ; 
 struct tv_mode* intel_tv_mode_find (struct intel_tv*) ; 

__attribute__((used)) static enum drm_mode_status
intel_tv_mode_valid(struct drm_connector *connector,
		    struct drm_display_mode *mode)
{
	struct intel_tv *intel_tv = intel_attached_tv(connector);
	const struct tv_mode *tv_mode = intel_tv_mode_find(intel_tv);

	/* Ensure TV refresh is close to desired refresh */
	if (tv_mode && abs(tv_mode->refresh - drm_mode_vrefresh(mode) * 1000)
				< 1000)
		return MODE_OK;

	return MODE_CLOCK_RANGE;
}