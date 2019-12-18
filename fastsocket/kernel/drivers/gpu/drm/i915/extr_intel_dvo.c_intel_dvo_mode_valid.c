#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* dev_ops; } ;
struct intel_dvo {TYPE_3__ dev; TYPE_1__* panel_fixed_mode; } ;
struct drm_display_mode {int flags; scalar_t__ hdisplay; scalar_t__ vdisplay; } ;
struct drm_connector {int dummy; } ;
struct TYPE_5__ {int (* mode_valid ) (TYPE_3__*,struct drm_display_mode*) ;} ;
struct TYPE_4__ {scalar_t__ hdisplay; scalar_t__ vdisplay; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_DBLSCAN ; 
 int MODE_NO_DBLESCAN ; 
 int MODE_PANEL ; 
 struct intel_dvo* intel_attached_dvo (struct drm_connector*) ; 
 int stub1 (TYPE_3__*,struct drm_display_mode*) ; 

__attribute__((used)) static int intel_dvo_mode_valid(struct drm_connector *connector,
				struct drm_display_mode *mode)
{
	struct intel_dvo *intel_dvo = intel_attached_dvo(connector);

	if (mode->flags & DRM_MODE_FLAG_DBLSCAN)
		return MODE_NO_DBLESCAN;

	/* XXX: Validate clock range */

	if (intel_dvo->panel_fixed_mode) {
		if (mode->hdisplay > intel_dvo->panel_fixed_mode->hdisplay)
			return MODE_PANEL;
		if (mode->vdisplay > intel_dvo->panel_fixed_mode->vdisplay)
			return MODE_PANEL;
	}

	return intel_dvo->dev.dev_ops->mode_valid(&intel_dvo->dev, mode);
}