#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nouveau_display {int /*<<< orphan*/  (* dtor ) (struct drm_device*) ;} ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * display; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_kms_helper_poll_fini (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  drm_vblank_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  kfree (struct nouveau_display*) ; 
 int /*<<< orphan*/  nouveau_backlight_exit (struct drm_device*) ; 
 struct nouveau_display* nouveau_display (struct drm_device*) ; 
 TYPE_1__* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  stub1 (struct drm_device*) ; 

void
nouveau_display_destroy(struct drm_device *dev)
{
	struct nouveau_display *disp = nouveau_display(dev);

	nouveau_backlight_exit(dev);
	drm_vblank_cleanup(dev);

	drm_kms_helper_poll_fini(dev);
	drm_mode_config_cleanup(dev);

	if (disp->dtor)
		disp->dtor(dev);

	nouveau_drm(dev)->display = NULL;
	kfree(disp);
}