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
struct intel_fbc_work {unsigned long interval; int /*<<< orphan*/  work; int /*<<< orphan*/  fb; struct drm_crtc* crtc; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable_fbc ) (struct drm_crtc*,unsigned long) ;} ;
struct drm_i915_private {struct intel_fbc_work* fbc_work; TYPE_1__ display; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct drm_crtc {int /*<<< orphan*/  fb; struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_cancel_fbc_work (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_fbc_work_fn ; 
 struct intel_fbc_work* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct drm_crtc*,unsigned long) ; 

void intel_enable_fbc(struct drm_crtc *crtc, unsigned long interval)
{
	struct intel_fbc_work *work;
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;

	if (!dev_priv->display.enable_fbc)
		return;

	intel_cancel_fbc_work(dev_priv);

	work = kzalloc(sizeof *work, GFP_KERNEL);
	if (work == NULL) {
		dev_priv->display.enable_fbc(crtc, interval);
		return;
	}

	work->crtc = crtc;
	work->fb = crtc->fb;
	work->interval = interval;
	INIT_DELAYED_WORK(&work->work, intel_fbc_work_fn);

	dev_priv->fbc_work = work;

	DRM_DEBUG_KMS("scheduling delayed FBC enable\n");

	/* Delay the actual enabling to let pageflipping cease and the
	 * display to settle before starting the compression. Note that
	 * this delay also serves a second purpose: it allows for a
	 * vblank to pass after disabling the FBC before we attempt
	 * to modify the control registers.
	 *
	 * A more complicated solution would involve tracking vblanks
	 * following the termination of the page-flipping sequence
	 * and indeed performing the enable as a co-routine and not
	 * waiting synchronously upon the vblank.
	 */
	schedule_delayed_work(&work->work, msecs_to_jiffies(50));
}