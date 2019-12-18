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
struct TYPE_2__ {int (* update_plane ) (struct drm_crtc*,struct drm_framebuffer*,int,int) ;int /*<<< orphan*/  (* disable_fbc ) (struct drm_device*) ;} ;
struct drm_i915_private {TYPE_1__ display; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;
typedef  enum mode_set_atomic { ____Placeholder_mode_set_atomic } mode_set_atomic ;

/* Variables and functions */
 int /*<<< orphan*/  intel_increase_pllclock (struct drm_crtc*) ; 
 int /*<<< orphan*/  stub1 (struct drm_device*) ; 
 int stub2 (struct drm_crtc*,struct drm_framebuffer*,int,int) ; 

__attribute__((used)) static int
intel_pipe_set_base_atomic(struct drm_crtc *crtc, struct drm_framebuffer *fb,
			   int x, int y, enum mode_set_atomic state)
{
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;

	if (dev_priv->display.disable_fbc)
		dev_priv->display.disable_fbc(dev);
	intel_increase_pllclock(crtc);

	return dev_priv->display.update_plane(crtc, fb, x, y);
}