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
struct nouveau_drm {TYPE_2__* fbcon; } ;
struct drm_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  fbdev; } ;
struct TYPE_4__ {TYPE_1__ helper; } ;

/* Variables and functions */
 int /*<<< orphan*/  console_lock () ; 
 int /*<<< orphan*/  console_unlock () ; 
 int /*<<< orphan*/  fb_set_suspend (int /*<<< orphan*/ ,int) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_fbcon_restore_accel (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_fbcon_save_disable_accel (struct drm_device*) ; 

void nouveau_fbcon_set_suspend(struct drm_device *dev, int state)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	console_lock();
	if (state == 0)
		nouveau_fbcon_save_disable_accel(dev);
	fb_set_suspend(drm->fbcon->helper.fbdev, state);
	if (state == 1)
		nouveau_fbcon_restore_accel(dev);
	console_unlock();
}