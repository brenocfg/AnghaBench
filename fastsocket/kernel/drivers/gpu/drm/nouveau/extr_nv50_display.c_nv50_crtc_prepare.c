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
typedef  int /*<<< orphan*/  u32 ;
struct nv50_mast {int dummy; } ;
struct nouveau_crtc {int index; } ;
struct drm_crtc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ NV84_DISP_MAST_CLASS ; 
 scalar_t__ NVD0_DISP_MAST_CLASS ; 
 int /*<<< orphan*/  evo_data (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  evo_kick (int /*<<< orphan*/ *,struct nv50_mast*) ; 
 int /*<<< orphan*/  evo_mthd (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * evo_wait (struct nv50_mast*,int) ; 
 struct nouveau_crtc* nouveau_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  nv50_crtc_cursor_show_hide (struct nouveau_crtc*,int,int) ; 
 int /*<<< orphan*/  nv50_display_flip_stop (struct drm_crtc*) ; 
 struct nv50_mast* nv50_mast (int /*<<< orphan*/ ) ; 
 scalar_t__ nv50_vers (struct nv50_mast*) ; 

__attribute__((used)) static void
nv50_crtc_prepare(struct drm_crtc *crtc)
{
	struct nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
	struct nv50_mast *mast = nv50_mast(crtc->dev);
	u32 *push;

	nv50_display_flip_stop(crtc);

	push = evo_wait(mast, 2);
	if (push) {
		if (nv50_vers(mast) < NV84_DISP_MAST_CLASS) {
			evo_mthd(push, 0x0874 + (nv_crtc->index * 0x400), 1);
			evo_data(push, 0x00000000);
			evo_mthd(push, 0x0840 + (nv_crtc->index * 0x400), 1);
			evo_data(push, 0x40000000);
		} else
		if (nv50_vers(mast) <  NVD0_DISP_MAST_CLASS) {
			evo_mthd(push, 0x0874 + (nv_crtc->index * 0x400), 1);
			evo_data(push, 0x00000000);
			evo_mthd(push, 0x0840 + (nv_crtc->index * 0x400), 1);
			evo_data(push, 0x40000000);
			evo_mthd(push, 0x085c + (nv_crtc->index * 0x400), 1);
			evo_data(push, 0x00000000);
		} else {
			evo_mthd(push, 0x0474 + (nv_crtc->index * 0x300), 1);
			evo_data(push, 0x00000000);
			evo_mthd(push, 0x0440 + (nv_crtc->index * 0x300), 1);
			evo_data(push, 0x03000000);
			evo_mthd(push, 0x045c + (nv_crtc->index * 0x300), 1);
			evo_data(push, 0x00000000);
		}

		evo_kick(push, mast);
	}

	nv50_crtc_cursor_show_hide(nv_crtc, false, false);
}