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
typedef  int u32 ;
struct nv50_mast {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct nouveau_crtc {int color_vibrance; int vibrant_hue; int index; TYPE_1__ base; } ;

/* Variables and functions */
 scalar_t__ NVD0_DISP_MAST_CLASS ; 
 int /*<<< orphan*/  evo_data (int*,int) ; 
 int /*<<< orphan*/  evo_kick (int*,struct nv50_mast*) ; 
 int /*<<< orphan*/  evo_mthd (int*,int,int) ; 
 int* evo_wait (struct nv50_mast*,int) ; 
 struct nv50_mast* nv50_mast (int /*<<< orphan*/ ) ; 
 scalar_t__ nv50_vers (struct nv50_mast*) ; 

__attribute__((used)) static int
nv50_crtc_set_color_vibrance(struct nouveau_crtc *nv_crtc, bool update)
{
	struct nv50_mast *mast = nv50_mast(nv_crtc->base.dev);
	u32 *push, hue, vib;
	int adj;

	adj = (nv_crtc->color_vibrance > 0) ? 50 : 0;
	vib = ((nv_crtc->color_vibrance * 2047 + adj) / 100) & 0xfff;
	hue = ((nv_crtc->vibrant_hue * 2047) / 100) & 0xfff;

	push = evo_wait(mast, 16);
	if (push) {
		if (nv50_vers(mast) < NVD0_DISP_MAST_CLASS) {
			evo_mthd(push, 0x08a8 + (nv_crtc->index * 0x400), 1);
			evo_data(push, (hue << 20) | (vib << 8));
		} else {
			evo_mthd(push, 0x0498 + (nv_crtc->index * 0x300), 1);
			evo_data(push, (hue << 20) | (vib << 8));
		}

		if (update) {
			evo_mthd(push, 0x0080, 1);
			evo_data(push, 0x00000000);
		}
		evo_kick(push, mast);
	}

	return 0;
}