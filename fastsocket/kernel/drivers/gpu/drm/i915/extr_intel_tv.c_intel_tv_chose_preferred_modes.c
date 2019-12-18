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
struct tv_mode {int nbr_end; int progressive; } ;
struct intel_tv {int dummy; } ;
struct drm_display_mode {int vdisplay; int /*<<< orphan*/  type; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_TYPE_PREFERRED ; 
 struct intel_tv* intel_attached_tv (struct drm_connector*) ; 
 struct tv_mode* intel_tv_mode_find (struct intel_tv*) ; 

__attribute__((used)) static void
intel_tv_chose_preferred_modes(struct drm_connector *connector,
			       struct drm_display_mode *mode_ptr)
{
	struct intel_tv *intel_tv = intel_attached_tv(connector);
	const struct tv_mode *tv_mode = intel_tv_mode_find(intel_tv);

	if (tv_mode->nbr_end < 480 && mode_ptr->vdisplay == 480)
		mode_ptr->type |= DRM_MODE_TYPE_PREFERRED;
	else if (tv_mode->nbr_end > 480) {
		if (tv_mode->progressive == true && tv_mode->nbr_end < 720) {
			if (mode_ptr->vdisplay == 720)
				mode_ptr->type |= DRM_MODE_TYPE_PREFERRED;
		} else if (mode_ptr->vdisplay == 1080)
				mode_ptr->type |= DRM_MODE_TYPE_PREFERRED;
	}
}