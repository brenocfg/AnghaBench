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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  event; } ;
struct TYPE_5__ {TYPE_1__ vblank; } ;
struct nvc0_software_chan {TYPE_2__ base; } ;
struct nouveau_object {int /*<<< orphan*/  parent; } ;
struct nouveau_disp {int /*<<< orphan*/  vblank; } ;
struct TYPE_6__ {scalar_t__ card_type; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NV_E0 ; 
 struct nouveau_disp* nouveau_disp (struct nouveau_object*) ; 
 int /*<<< orphan*/  nouveau_event_get (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 TYPE_3__* nv_device (struct nouveau_object*) ; 
 scalar_t__ nv_engctx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nvc0_software_mthd_vblsem_release(struct nouveau_object *object, u32 mthd,
				  void *args, u32 size)
{
	struct nvc0_software_chan *chan = (void *)nv_engctx(object->parent);
	struct nouveau_disp *disp = nouveau_disp(object);
	u32 crtc = *(u32 *)args;

	if ((nv_device(object)->card_type < NV_E0 && crtc > 1) || crtc > 3)
		return -EINVAL;

	nouveau_event_get(disp->vblank, crtc, &chan->base.vblank.event);
	return 0;
}