#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct intel_plane {int /*<<< orphan*/ * obj; int /*<<< orphan*/  (* disable_plane ) (struct drm_plane*) ;} ;
struct drm_plane {scalar_t__ crtc; struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_enable_primary (scalar_t__) ; 
 int /*<<< orphan*/  intel_unpin_fb_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct drm_plane*) ; 
 struct intel_plane* to_intel_plane (struct drm_plane*) ; 

__attribute__((used)) static int
intel_disable_plane(struct drm_plane *plane)
{
	struct drm_device *dev = plane->dev;
	struct intel_plane *intel_plane = to_intel_plane(plane);
	int ret = 0;

	if (plane->crtc)
		intel_enable_primary(plane->crtc);
	intel_plane->disable_plane(plane);

	if (!intel_plane->obj)
		goto out;

	mutex_lock(&dev->struct_mutex);
	intel_unpin_fb_obj(intel_plane->obj);
	intel_plane->obj = NULL;
	mutex_unlock(&dev->struct_mutex);
out:

	return ret;
}