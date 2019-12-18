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
struct nouveau_drm {int /*<<< orphan*/  client; } ;
struct TYPE_2__ {scalar_t__ num_crtc; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_accel_fini (struct nouveau_drm*) ; 
 int /*<<< orphan*/  nouveau_agp_fini (struct nouveau_drm*) ; 
 int /*<<< orphan*/  nouveau_bios_takedown (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_cli_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_display_destroy (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_display_fini (struct drm_device*) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_fbcon_fini (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_irq_fini (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_pm_fini (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_ttm_fini (struct nouveau_drm*) ; 
 int /*<<< orphan*/  nouveau_vga_fini (struct nouveau_drm*) ; 

__attribute__((used)) static int
nouveau_drm_unload(struct drm_device *dev)
{
	struct nouveau_drm *drm = nouveau_drm(dev);

	nouveau_fbcon_fini(dev);
	nouveau_accel_fini(drm);

	nouveau_pm_fini(dev);

	if (dev->mode_config.num_crtc)
		nouveau_display_fini(dev);
	nouveau_display_destroy(dev);

	nouveau_irq_fini(dev);
	nouveau_bios_takedown(dev);

	nouveau_ttm_fini(drm);
	nouveau_agp_fini(drm);
	nouveau_vga_fini(drm);

	nouveau_cli_destroy(&drm->client);
	return 0;
}