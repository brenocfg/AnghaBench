#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ reg; } ;
struct TYPE_5__ {TYPE_1__ pll; } ;
struct nv04_pm_state {TYPE_2__ memory; TYPE_2__ core; } ;
struct nouveau_timer {int dummy; } ;
struct nouveau_device {scalar_t__ card_type; } ;
struct drm_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ NV_20 ; 
 scalar_t__ NV_30 ; 
 int /*<<< orphan*/  kfree (struct nv04_pm_state*) ; 
 struct nouveau_device* nouveau_dev (struct drm_device*) ; 
 struct nouveau_timer* nouveau_timer (struct nouveau_device*) ; 
 int /*<<< orphan*/  nv_mask (struct nouveau_device*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nv_object (struct nouveau_timer*) ; 
 TYPE_3__* nv_ofuncs (struct nouveau_timer*) ; 
 int /*<<< orphan*/  prog_pll (struct drm_device*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

int
nv04_pm_clocks_set(struct drm_device *dev, void *pre_state)
{
	struct nouveau_device *device = nouveau_dev(dev);
	struct nouveau_timer *ptimer = nouveau_timer(device);
	struct nv04_pm_state *state = pre_state;

	prog_pll(dev, &state->core);

	if (state->memory.pll.reg) {
		prog_pll(dev, &state->memory);
		if (device->card_type < NV_30) {
			if (device->card_type == NV_20)
				nv_mask(device, 0x1002c4, 0, 1 << 20);

			/* Reset the DLLs */
			nv_mask(device, 0x1002c0, 0, 1 << 8);
		}
	}

	nv_ofuncs(ptimer)->init(nv_object(ptimer));

	kfree(state);
	return 0;
}