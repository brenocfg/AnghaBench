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
struct nouveau_drm {TYPE_1__* fbcon; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  helper; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_fb_helper_hotplug_event (int /*<<< orphan*/ *) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 

void
nouveau_fbcon_output_poll_changed(struct drm_device *dev)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	drm_fb_helper_hotplug_event(&drm->fbcon->helper);
}