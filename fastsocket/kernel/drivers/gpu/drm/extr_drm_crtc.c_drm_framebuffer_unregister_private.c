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
struct drm_framebuffer {struct drm_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  fb_lock; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  __drm_framebuffer_unregister (struct drm_device*,struct drm_framebuffer*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void drm_framebuffer_unregister_private(struct drm_framebuffer *fb)
{
	struct drm_device *dev = fb->dev;

	mutex_lock(&dev->mode_config.fb_lock);
	/* Mark fb as reaped and drop idr ref. */
	__drm_framebuffer_unregister(dev, fb);
	mutex_unlock(&dev->mode_config.fb_lock);
}