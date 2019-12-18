#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct drm_crtc* crtc; } ;
struct TYPE_8__ {int connectors_active; TYPE_1__ base; } ;
struct TYPE_9__ {TYPE_2__* dev_ops; } ;
struct intel_dvo {TYPE_3__ base; TYPE_4__ dev; } ;
struct drm_crtc {int dummy; } ;
struct drm_connector {int dpms; int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* dpms ) (TYPE_4__*,int) ;} ;

/* Variables and functions */
 int DRM_MODE_DPMS_OFF ; 
 int DRM_MODE_DPMS_ON ; 
 struct intel_dvo* intel_attached_dvo (struct drm_connector*) ; 
 int /*<<< orphan*/  intel_crtc_update_dpms (struct drm_crtc*) ; 
 int /*<<< orphan*/  intel_modeset_check_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,int) ; 

__attribute__((used)) static void intel_dvo_dpms(struct drm_connector *connector, int mode)
{
	struct intel_dvo *intel_dvo = intel_attached_dvo(connector);
	struct drm_crtc *crtc;

	/* dvo supports only 2 dpms states. */
	if (mode != DRM_MODE_DPMS_ON)
		mode = DRM_MODE_DPMS_OFF;

	if (mode == connector->dpms)
		return;

	connector->dpms = mode;

	/* Only need to change hw state when actually enabled */
	crtc = intel_dvo->base.base.crtc;
	if (!crtc) {
		intel_dvo->base.connectors_active = false;
		return;
	}

	if (mode == DRM_MODE_DPMS_ON) {
		intel_dvo->base.connectors_active = true;

		intel_crtc_update_dpms(crtc);

		intel_dvo->dev.dev_ops->dpms(&intel_dvo->dev, true);
	} else {
		intel_dvo->dev.dev_ops->dpms(&intel_dvo->dev, false);

		intel_dvo->base.connectors_active = false;

		intel_crtc_update_dpms(crtc);
	}

	intel_modeset_check_state(connector->dev);
}