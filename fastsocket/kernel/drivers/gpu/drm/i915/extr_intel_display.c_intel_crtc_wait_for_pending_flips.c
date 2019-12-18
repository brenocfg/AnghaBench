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
struct drm_i915_private {int /*<<< orphan*/  pending_flip_queue; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; struct drm_i915_private* dev_private; } ;
struct drm_crtc {int /*<<< orphan*/ * fb; struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_crtc_has_pending_flip (struct drm_crtc*) ; 
 int /*<<< orphan*/  intel_finish_fb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  waitqueue_active (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void intel_crtc_wait_for_pending_flips(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;

	if (crtc->fb == NULL)
		return;

	WARN_ON(waitqueue_active(&dev_priv->pending_flip_queue));

	wait_event(dev_priv->pending_flip_queue,
		   !intel_crtc_has_pending_flip(crtc));

	mutex_lock(&dev->struct_mutex);
	intel_finish_fb(crtc->fb);
	mutex_unlock(&dev->struct_mutex);
}