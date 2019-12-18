#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct intel_unpin_work {struct drm_i915_gem_object* pending_flip_obj; int /*<<< orphan*/  enable_stall_check; int /*<<< orphan*/  pending; } ;
struct intel_crtc {int /*<<< orphan*/  plane; struct intel_unpin_work* unpin_work; } ;
struct drm_i915_gem_object {scalar_t__ gtt_offset; } ;
struct drm_device {int /*<<< orphan*/  event_lock; TYPE_2__* dev_private; } ;
struct drm_crtc {int y; int x; TYPE_1__* fb; } ;
struct TYPE_5__ {struct drm_crtc** pipe_to_crtc_mapping; } ;
typedef  TYPE_2__ drm_i915_private_t ;
struct TYPE_6__ {int gen; } ;
struct TYPE_4__ {int* pitches; int bits_per_pixel; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int DSPADDR (int /*<<< orphan*/ ) ; 
 int DSPSURF (int /*<<< orphan*/ ) ; 
 scalar_t__ I915_HI_DISPBASE (scalar_t__) ; 
 scalar_t__ I915_READ (int) ; 
 scalar_t__ INTEL_FLIP_COMPLETE ; 
 TYPE_3__* INTEL_INFO (struct drm_device*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_prepare_page_flip (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void i915_pageflip_stall_check(struct drm_device *dev, int pipe)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	struct drm_crtc *crtc = dev_priv->pipe_to_crtc_mapping[pipe];
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	struct drm_i915_gem_object *obj;
	struct intel_unpin_work *work;
	unsigned long flags;
	bool stall_detected;

	/* Ignore early vblank irqs */
	if (intel_crtc == NULL)
		return;

	spin_lock_irqsave(&dev->event_lock, flags);
	work = intel_crtc->unpin_work;

	if (work == NULL ||
	    atomic_read(&work->pending) >= INTEL_FLIP_COMPLETE ||
	    !work->enable_stall_check) {
		/* Either the pending flip IRQ arrived, or we're too early. Don't check */
		spin_unlock_irqrestore(&dev->event_lock, flags);
		return;
	}

	/* Potential stall - if we see that the flip has happened, assume a missed interrupt */
	obj = work->pending_flip_obj;
	if (INTEL_INFO(dev)->gen >= 4) {
		int dspsurf = DSPSURF(intel_crtc->plane);
		stall_detected = I915_HI_DISPBASE(I915_READ(dspsurf)) ==
					obj->gtt_offset;
	} else {
		int dspaddr = DSPADDR(intel_crtc->plane);
		stall_detected = I915_READ(dspaddr) == (obj->gtt_offset +
							crtc->y * crtc->fb->pitches[0] +
							crtc->x * crtc->fb->bits_per_pixel/8);
	}

	spin_unlock_irqrestore(&dev->event_lock, flags);

	if (stall_detected) {
		DRM_DEBUG_DRIVER("Pageflip stall detected\n");
		intel_prepare_page_flip(dev, intel_crtc->plane);
	}
}