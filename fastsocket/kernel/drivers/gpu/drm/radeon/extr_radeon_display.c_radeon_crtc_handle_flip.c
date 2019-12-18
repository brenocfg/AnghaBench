#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct timeval {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct radeon_unpin_work {int /*<<< orphan*/  work; int /*<<< orphan*/  crtc_id; int /*<<< orphan*/  rdev; scalar_t__ fence; struct drm_pending_vblank_event* event; int /*<<< orphan*/  new_crtc_base; } ;
struct TYPE_12__ {struct radeon_crtc** crtcs; } ;
struct radeon_device {TYPE_7__* ddev; TYPE_3__ mode_info; } ;
struct TYPE_10__ {int crtc_vdisplay; } ;
struct TYPE_11__ {TYPE_1__ hwmode; } ;
struct radeon_crtc {int deferred_flip_completion; int /*<<< orphan*/  crtc_id; struct radeon_unpin_work* unpin_work; TYPE_2__ base; } ;
struct TYPE_15__ {TYPE_5__* file_priv; int /*<<< orphan*/  link; } ;
struct TYPE_13__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; int /*<<< orphan*/  sequence; } ;
struct drm_pending_vblank_event {TYPE_6__ base; TYPE_4__ event; } ;
struct TYPE_16__ {int /*<<< orphan*/  event_lock; } ;
struct TYPE_14__ {int /*<<< orphan*/  event_wait; int /*<<< orphan*/  event_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_IS_AVIVO (struct radeon_device*) ; 
 int DRM_SCANOUTPOS_VALID ; 
 int /*<<< orphan*/  drm_vblank_count_and_time (TYPE_7__*,int,struct timeval*) ; 
 int /*<<< orphan*/  drm_vblank_put (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_fence_signaled (scalar_t__) ; 
 int /*<<< orphan*/  radeon_fence_unref (scalar_t__*) ; 
 int radeon_get_crtc_scanoutpos (TYPE_7__*,int,int*,int*) ; 
 scalar_t__ radeon_page_flip (struct radeon_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_post_page_flip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void radeon_crtc_handle_flip(struct radeon_device *rdev, int crtc_id)
{
	struct radeon_crtc *radeon_crtc = rdev->mode_info.crtcs[crtc_id];
	struct radeon_unpin_work *work;
	struct drm_pending_vblank_event *e;
	struct timeval now;
	unsigned long flags;
	u32 update_pending;
	int vpos, hpos;

	spin_lock_irqsave(&rdev->ddev->event_lock, flags);
	work = radeon_crtc->unpin_work;
	if (work == NULL ||
	    (work->fence && !radeon_fence_signaled(work->fence))) {
		spin_unlock_irqrestore(&rdev->ddev->event_lock, flags);
		return;
	}
	/* New pageflip, or just completion of a previous one? */
	if (!radeon_crtc->deferred_flip_completion) {
		/* do the flip (mmio) */
		update_pending = radeon_page_flip(rdev, crtc_id, work->new_crtc_base);
	} else {
		/* This is just a completion of a flip queued in crtc
		 * at last invocation. Make sure we go directly to
		 * completion routine.
		 */
		update_pending = 0;
		radeon_crtc->deferred_flip_completion = 0;
	}

	/* Has the pageflip already completed in crtc, or is it certain
	 * to complete in this vblank?
	 */
	if (update_pending &&
	    (DRM_SCANOUTPOS_VALID & radeon_get_crtc_scanoutpos(rdev->ddev, crtc_id,
							       &vpos, &hpos)) &&
	    ((vpos >= (99 * rdev->mode_info.crtcs[crtc_id]->base.hwmode.crtc_vdisplay)/100) ||
	     (vpos < 0 && !ASIC_IS_AVIVO(rdev)))) {
		/* crtc didn't flip in this target vblank interval,
		 * but flip is pending in crtc. Based on the current
		 * scanout position we know that the current frame is
		 * (nearly) complete and the flip will (likely)
		 * complete before the start of the next frame.
		 */
		update_pending = 0;
	}
	if (update_pending) {
		/* crtc didn't flip in this target vblank interval,
		 * but flip is pending in crtc. It will complete it
		 * in next vblank interval, so complete the flip at
		 * next vblank irq.
		 */
		radeon_crtc->deferred_flip_completion = 1;
		spin_unlock_irqrestore(&rdev->ddev->event_lock, flags);
		return;
	}

	/* Pageflip (will be) certainly completed in this vblank. Clean up. */
	radeon_crtc->unpin_work = NULL;

	/* wakeup userspace */
	if (work->event) {
		e = work->event;
		e->event.sequence = drm_vblank_count_and_time(rdev->ddev, crtc_id, &now);
		e->event.tv_sec = now.tv_sec;
		e->event.tv_usec = now.tv_usec;
		list_add_tail(&e->base.link, &e->base.file_priv->event_list);
		wake_up_interruptible(&e->base.file_priv->event_wait);
	}
	spin_unlock_irqrestore(&rdev->ddev->event_lock, flags);

	drm_vblank_put(rdev->ddev, radeon_crtc->crtc_id);
	radeon_fence_unref(&work->fence);
	radeon_post_page_flip(work->rdev, work->crtc_id);
	schedule_work(&work->work);
}