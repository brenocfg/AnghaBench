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
struct nv50_display_flip {int /*<<< orphan*/  chan; int /*<<< orphan*/  disp; } ;
struct nouveau_device {int dummy; } ;
struct drm_crtc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  evo_data (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  evo_kick (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evo_mthd (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * evo_wait (int /*<<< orphan*/ ,int) ; 
 struct nouveau_device* nouveau_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv50_disp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv50_display_flip_wait ; 
 int /*<<< orphan*/  nv50_sync (struct drm_crtc*) ; 
 int /*<<< orphan*/  nv_wait_cb (struct nouveau_device*,int /*<<< orphan*/ ,struct nv50_display_flip*) ; 

void
nv50_display_flip_stop(struct drm_crtc *crtc)
{
	struct nouveau_device *device = nouveau_dev(crtc->dev);
	struct nv50_display_flip flip = {
		.disp = nv50_disp(crtc->dev),
		.chan = nv50_sync(crtc),
	};
	u32 *push;

	push = evo_wait(flip.chan, 8);
	if (push) {
		evo_mthd(push, 0x0084, 1);
		evo_data(push, 0x00000000);
		evo_mthd(push, 0x0094, 1);
		evo_data(push, 0x00000000);
		evo_mthd(push, 0x00c0, 1);
		evo_data(push, 0x00000000);
		evo_mthd(push, 0x0080, 1);
		evo_data(push, 0x00000000);
		evo_kick(push, flip.chan);
	}

	nv_wait_cb(device, nv50_display_flip_wait, &flip);
}