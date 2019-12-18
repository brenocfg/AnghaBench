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
struct intel_unpin_work {int /*<<< orphan*/  pending_flip_obj; int /*<<< orphan*/  work; struct drm_i915_gem_object* old_fb_obj; scalar_t__ event; int /*<<< orphan*/  pending; } ;
struct intel_crtc {int /*<<< orphan*/  plane; int /*<<< orphan*/  pipe; struct intel_unpin_work* unpin_work; } ;
struct drm_i915_gem_object {int dummy; } ;
struct drm_device {int /*<<< orphan*/  event_lock; TYPE_1__* dev_private; } ;
struct drm_crtc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  wq; int /*<<< orphan*/  pending_flip_queue; } ;
typedef  TYPE_1__ drm_i915_private_t ;

/* Variables and functions */
 scalar_t__ INTEL_FLIP_COMPLETE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_send_vblank_event (struct drm_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  drm_vblank_put (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  trace_i915_flip_complete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_intel_finish_page_flip(struct drm_device *dev,
				      struct drm_crtc *crtc)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	struct intel_unpin_work *work;
	struct drm_i915_gem_object *obj;
	unsigned long flags;

	/* Ignore early vblank irqs */
	if (intel_crtc == NULL)
		return;

	spin_lock_irqsave(&dev->event_lock, flags);
	work = intel_crtc->unpin_work;

	/* Ensure we don't miss a work->pending update ... */
	smp_rmb();

	if (work == NULL || atomic_read(&work->pending) < INTEL_FLIP_COMPLETE) {
		spin_unlock_irqrestore(&dev->event_lock, flags);
		return;
	}

	/* and that the unpin work is consistent wrt ->pending. */
	smp_rmb();

	intel_crtc->unpin_work = NULL;

	if (work->event)
		drm_send_vblank_event(dev, intel_crtc->pipe, work->event);

	drm_vblank_put(dev, intel_crtc->pipe);

	spin_unlock_irqrestore(&dev->event_lock, flags);

	obj = work->old_fb_obj;

	wake_up_all(&dev_priv->pending_flip_queue);

	queue_work(dev_priv->wq, &work->work);

	trace_i915_flip_complete(intel_crtc->plane, work->pending_flip_obj);
}