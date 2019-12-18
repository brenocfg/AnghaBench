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
typedef  int u16 ;
struct radeon_crtc {int* lut_r; int* lut_g; int* lut_b; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 struct radeon_crtc* to_radeon_crtc (struct drm_crtc*) ; 

void radeon_crtc_fb_gamma_set(struct drm_crtc *crtc, u16 red, u16 green,
			      u16 blue, int regno)
{
	struct radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);

	radeon_crtc->lut_r[regno] = red >> 6;
	radeon_crtc->lut_g[regno] = green >> 6;
	radeon_crtc->lut_b[regno] = blue >> 6;
}