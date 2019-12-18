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
struct intel_crtc {int pipe; } ;
struct drm_i915_master_private {TYPE_1__* sarea_priv; } ;
struct drm_device {TYPE_3__* primary; } ;
struct drm_crtc {struct drm_device* dev; } ;
struct TYPE_6__ {TYPE_2__* master; } ;
struct TYPE_5__ {struct drm_i915_master_private* driver_priv; } ;
struct TYPE_4__ {int pipeA_x; int pipeA_y; int pipeB_x; int pipeB_y; } ;

/* Variables and functions */
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void intel_crtc_update_sarea_pos(struct drm_crtc *crtc, int x, int y)
{
	struct drm_device *dev = crtc->dev;
	struct drm_i915_master_private *master_priv;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);

	if (!dev->primary->master)
		return;

	master_priv = dev->primary->master->driver_priv;
	if (!master_priv->sarea_priv)
		return;

	switch (intel_crtc->pipe) {
	case 0:
		master_priv->sarea_priv->pipeA_x = x;
		master_priv->sarea_priv->pipeA_y = y;
		break;
	case 1:
		master_priv->sarea_priv->pipeB_x = x;
		master_priv->sarea_priv->pipeB_y = y;
		break;
	default:
		break;
	}
}