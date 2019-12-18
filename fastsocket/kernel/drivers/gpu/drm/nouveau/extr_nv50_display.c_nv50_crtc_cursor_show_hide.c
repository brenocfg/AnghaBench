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
typedef  int /*<<< orphan*/  u32 ;
struct nv50_mast {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct nouveau_crtc {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  evo_data (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  evo_kick (int /*<<< orphan*/ *,struct nv50_mast*) ; 
 int /*<<< orphan*/  evo_mthd (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * evo_wait (struct nv50_mast*,int) ; 
 int /*<<< orphan*/  nv50_crtc_cursor_hide (struct nouveau_crtc*) ; 
 int /*<<< orphan*/  nv50_crtc_cursor_show (struct nouveau_crtc*) ; 
 struct nv50_mast* nv50_mast (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nv50_crtc_cursor_show_hide(struct nouveau_crtc *nv_crtc, bool show, bool update)
{
	struct nv50_mast *mast = nv50_mast(nv_crtc->base.dev);

	if (show)
		nv50_crtc_cursor_show(nv_crtc);
	else
		nv50_crtc_cursor_hide(nv_crtc);

	if (update) {
		u32 *push = evo_wait(mast, 2);
		if (push) {
			evo_mthd(push, 0x0080, 1);
			evo_data(push, 0x00000000);
			evo_kick(push, mast);
		}
	}
}