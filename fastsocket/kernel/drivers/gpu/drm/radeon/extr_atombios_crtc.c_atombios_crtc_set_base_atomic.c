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
struct radeon_device {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;
typedef  enum mode_set_atomic { ____Placeholder_mode_set_atomic } mode_set_atomic ;

/* Variables and functions */
 scalar_t__ ASIC_IS_AVIVO (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE4 (struct radeon_device*) ; 
 int avivo_crtc_do_set_base (struct drm_crtc*,struct drm_framebuffer*,int,int,int) ; 
 int dce4_crtc_do_set_base (struct drm_crtc*,struct drm_framebuffer*,int,int,int) ; 
 int radeon_crtc_do_set_base (struct drm_crtc*,struct drm_framebuffer*,int,int,int) ; 

int atombios_crtc_set_base_atomic(struct drm_crtc *crtc,
                                  struct drm_framebuffer *fb,
				  int x, int y, enum mode_set_atomic state)
{
       struct drm_device *dev = crtc->dev;
       struct radeon_device *rdev = dev->dev_private;

	if (ASIC_IS_DCE4(rdev))
		return dce4_crtc_do_set_base(crtc, fb, x, y, 1);
	else if (ASIC_IS_AVIVO(rdev))
		return avivo_crtc_do_set_base(crtc, fb, x, y, 1);
	else
		return radeon_crtc_do_set_base(crtc, fb, x, y, 1);
}