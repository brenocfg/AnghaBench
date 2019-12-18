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
typedef  void* u16 ;
struct TYPE_2__ {void** b; void** g; void** r; } ;
struct nouveau_crtc {TYPE_1__ lut; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 struct nouveau_crtc* nouveau_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void nouveau_fbcon_gamma_set(struct drm_crtc *crtc, u16 red, u16 green,
				    u16 blue, int regno)
{
	struct nouveau_crtc *nv_crtc = nouveau_crtc(crtc);

	nv_crtc->lut.r[regno] = red;
	nv_crtc->lut.g[regno] = green;
	nv_crtc->lut.b[regno] = blue;
}