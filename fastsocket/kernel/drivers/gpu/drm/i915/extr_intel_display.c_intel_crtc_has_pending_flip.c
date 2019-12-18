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
struct intel_crtc {scalar_t__ reset_counter; int /*<<< orphan*/ * unpin_work; } ;
struct TYPE_2__ {int /*<<< orphan*/  reset_counter; } ;
struct drm_i915_private {TYPE_1__ gpu_error; } ;
struct drm_device {int /*<<< orphan*/  event_lock; struct drm_i915_private* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ i915_reset_in_progress (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 

__attribute__((used)) static bool intel_crtc_has_pending_flip(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	unsigned long flags;
	bool pending;

	if (i915_reset_in_progress(&dev_priv->gpu_error) ||
	    intel_crtc->reset_counter != atomic_read(&dev_priv->gpu_error.reset_counter))
		return false;

	spin_lock_irqsave(&dev->event_lock, flags);
	pending = to_intel_crtc(crtc)->unpin_work != NULL;
	spin_unlock_irqrestore(&dev->event_lock, flags);

	return pending;
}