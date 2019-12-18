#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct nv50_mast {int dummy; } ;
struct nouveau_framebuffer {int r_pitch; int r_format; int r_dma; TYPE_3__* nvbo; } ;
struct TYPE_8__ {int tile_flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct nouveau_crtc {int index; TYPE_4__ fb; TYPE_1__ base; } ;
struct drm_framebuffer {int height; int width; } ;
struct TYPE_6__ {int offset; } ;
struct TYPE_7__ {TYPE_2__ bo; } ;

/* Variables and functions */
 scalar_t__ NV50_DISP_MAST_CLASS ; 
 scalar_t__ NVD0_DISP_MAST_CLASS ; 
 int /*<<< orphan*/  evo_data (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  evo_kick (int /*<<< orphan*/ *,struct nv50_mast*) ; 
 int /*<<< orphan*/  evo_mthd (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * evo_wait (struct nv50_mast*,int) ; 
 struct nouveau_framebuffer* nouveau_framebuffer (struct drm_framebuffer*) ; 
 struct nv50_mast* nv50_mast (int /*<<< orphan*/ ) ; 
 scalar_t__ nv50_vers (struct nv50_mast*) ; 

__attribute__((used)) static int
nv50_crtc_set_image(struct nouveau_crtc *nv_crtc, struct drm_framebuffer *fb,
		    int x, int y, bool update)
{
	struct nouveau_framebuffer *nvfb = nouveau_framebuffer(fb);
	struct nv50_mast *mast = nv50_mast(nv_crtc->base.dev);
	u32 *push;

	push = evo_wait(mast, 16);
	if (push) {
		if (nv50_vers(mast) < NVD0_DISP_MAST_CLASS) {
			evo_mthd(push, 0x0860 + (nv_crtc->index * 0x400), 1);
			evo_data(push, nvfb->nvbo->bo.offset >> 8);
			evo_mthd(push, 0x0868 + (nv_crtc->index * 0x400), 3);
			evo_data(push, (fb->height << 16) | fb->width);
			evo_data(push, nvfb->r_pitch);
			evo_data(push, nvfb->r_format);
			evo_mthd(push, 0x08c0 + (nv_crtc->index * 0x400), 1);
			evo_data(push, (y << 16) | x);
			if (nv50_vers(mast) > NV50_DISP_MAST_CLASS) {
				evo_mthd(push, 0x0874 + (nv_crtc->index * 0x400), 1);
				evo_data(push, nvfb->r_dma);
			}
		} else {
			evo_mthd(push, 0x0460 + (nv_crtc->index * 0x300), 1);
			evo_data(push, nvfb->nvbo->bo.offset >> 8);
			evo_mthd(push, 0x0468 + (nv_crtc->index * 0x300), 4);
			evo_data(push, (fb->height << 16) | fb->width);
			evo_data(push, nvfb->r_pitch);
			evo_data(push, nvfb->r_format);
			evo_data(push, nvfb->r_dma);
			evo_mthd(push, 0x04b0 + (nv_crtc->index * 0x300), 1);
			evo_data(push, (y << 16) | x);
		}

		if (update) {
			evo_mthd(push, 0x0080, 1);
			evo_data(push, 0x00000000);
		}
		evo_kick(push, mast);
	}

	nv_crtc->fb.tile_flags = nvfb->r_dma;
	return 0;
}