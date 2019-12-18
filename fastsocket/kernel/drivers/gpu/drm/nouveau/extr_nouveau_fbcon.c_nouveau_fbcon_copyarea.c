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
struct nouveau_fbdev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;
struct nouveau_drm {TYPE_1__ client; int /*<<< orphan*/  device; } ;
struct nouveau_device {scalar_t__ card_type; } ;
struct fb_info {scalar_t__ state; int flags; struct nouveau_fbdev* par; } ;
struct fb_copyarea {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int FBINFO_HWACCEL_DISABLED ; 
 scalar_t__ FBINFO_STATE_RUNNING ; 
 scalar_t__ NV_50 ; 
 scalar_t__ NV_C0 ; 
 int /*<<< orphan*/  cfb_copyarea (struct fb_info*,struct fb_copyarea const*) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 scalar_t__ mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nouveau_drm* nouveau_drm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_fbcon_gpu_lockup (struct fb_info*) ; 
 int nv04_fbcon_copyarea (struct fb_info*,struct fb_copyarea const*) ; 
 int nv50_fbcon_copyarea (struct fb_info*,struct fb_copyarea const*) ; 
 struct nouveau_device* nv_device (int /*<<< orphan*/ ) ; 
 int nvc0_fbcon_copyarea (struct fb_info*,struct fb_copyarea const*) ; 

__attribute__((used)) static void
nouveau_fbcon_copyarea(struct fb_info *info, const struct fb_copyarea *image)
{
	struct nouveau_fbdev *fbcon = info->par;
	struct nouveau_drm *drm = nouveau_drm(fbcon->dev);
	struct nouveau_device *device = nv_device(drm->device);
	int ret;

	if (info->state != FBINFO_STATE_RUNNING)
		return;

	ret = -ENODEV;
	if (!in_interrupt() && !(info->flags & FBINFO_HWACCEL_DISABLED) &&
	    mutex_trylock(&drm->client.mutex)) {
		if (device->card_type < NV_50)
			ret = nv04_fbcon_copyarea(info, image);
		else
		if (device->card_type < NV_C0)
			ret = nv50_fbcon_copyarea(info, image);
		else
			ret = nvc0_fbcon_copyarea(info, image);
		mutex_unlock(&drm->client.mutex);
	}

	if (ret == 0)
		return;

	if (ret != -ENODEV)
		nouveau_fbcon_gpu_lockup(info);
	cfb_copyarea(info, image);
}