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
struct TYPE_4__ {scalar_t__ id; } ;
struct drm_framebuffer {TYPE_2__ base; } ;
struct TYPE_3__ {int /*<<< orphan*/  idr_mutex; int /*<<< orphan*/  crtc_idr; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  __drm_framebuffer_unreference (struct drm_framebuffer*) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __drm_framebuffer_unregister(struct drm_device *dev,
					 struct drm_framebuffer *fb)
{
	mutex_lock(&dev->mode_config.idr_mutex);
	idr_remove(&dev->mode_config.crtc_idr, fb->base.id);
	mutex_unlock(&dev->mode_config.idr_mutex);

	fb->base.id = 0;

	__drm_framebuffer_unreference(fb);
}