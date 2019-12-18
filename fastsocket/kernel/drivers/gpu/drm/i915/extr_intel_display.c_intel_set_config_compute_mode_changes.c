#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct intel_set_config {int mode_changed; int fb_changed; } ;
struct drm_mode_set {scalar_t__ x; scalar_t__ y; int /*<<< orphan*/ * mode; TYPE_2__* crtc; TYPE_1__* fb; int /*<<< orphan*/  num_connectors; int /*<<< orphan*/ * connectors; } ;
struct TYPE_4__ {scalar_t__ x; scalar_t__ y; int /*<<< orphan*/  mode; TYPE_1__* fb; } ;
struct TYPE_3__ {scalar_t__ depth; scalar_t__ bits_per_pixel; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  drm_mode_debug_printmodeline (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mode_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ is_crtc_connector_off (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
intel_set_config_compute_mode_changes(struct drm_mode_set *set,
				      struct intel_set_config *config)
{

	/* We should be able to check here if the fb has the same properties
	 * and then just flip_or_move it */
	if (set->connectors != NULL &&
	    is_crtc_connector_off(set->crtc, *set->connectors,
				  set->num_connectors)) {
			config->mode_changed = true;
	} else if (set->crtc->fb != set->fb) {
		/* If we have no fb then treat it as a full mode set */
		if (set->crtc->fb == NULL) {
			DRM_DEBUG_KMS("crtc has no fb, full mode set\n");
			config->mode_changed = true;
		} else if (set->fb == NULL) {
			config->mode_changed = true;
		} else if (set->fb->depth != set->crtc->fb->depth) {
			config->mode_changed = true;
		} else if (set->fb->bits_per_pixel !=
			   set->crtc->fb->bits_per_pixel) {
			config->mode_changed = true;
		} else {
			config->fb_changed = true;
		}
	}

	if (set->fb && (set->x != set->crtc->x || set->y != set->crtc->y))
		config->fb_changed = true;

	if (set->mode && !drm_mode_equal(set->mode, &set->crtc->mode)) {
		DRM_DEBUG_KMS("modes are different, full mode set\n");
		drm_mode_debug_printmodeline(&set->crtc->mode);
		drm_mode_debug_printmodeline(set->mode);
		config->mode_changed = true;
	}
}