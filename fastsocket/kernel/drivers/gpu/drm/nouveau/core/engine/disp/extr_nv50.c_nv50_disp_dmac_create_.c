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
struct nv50_disp_dmac {int push; TYPE_1__* pushdma; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct TYPE_2__ {int limit; int start; int /*<<< orphan*/  target; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
#define  NV_MEM_TARGET_PCI_NOSNOOP 129 
#define  NV_MEM_TARGET_VRAM 128 
 scalar_t__ nouveau_handle_ref (struct nouveau_object*,int /*<<< orphan*/ ) ; 
 int nv50_disp_chan_create_ (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,int,int,void**) ; 
 int nv_mclass (TYPE_1__*) ; 

int
nv50_disp_dmac_create_(struct nouveau_object *parent,
		       struct nouveau_object *engine,
		       struct nouveau_oclass *oclass, u32 pushbuf, int chid,
		       int length, void **pobject)
{
	struct nv50_disp_dmac *dmac;
	int ret;

	ret = nv50_disp_chan_create_(parent, engine, oclass, chid,
				     length, pobject);
	dmac = *pobject;
	if (ret)
		return ret;

	dmac->pushdma = (void *)nouveau_handle_ref(parent, pushbuf);
	if (!dmac->pushdma)
		return -ENOENT;

	switch (nv_mclass(dmac->pushdma)) {
	case 0x0002:
	case 0x003d:
		if (dmac->pushdma->limit - dmac->pushdma->start != 0xfff)
			return -EINVAL;

		switch (dmac->pushdma->target) {
		case NV_MEM_TARGET_VRAM:
			dmac->push = 0x00000000 | dmac->pushdma->start >> 8;
			break;
		case NV_MEM_TARGET_PCI_NOSNOOP:
			dmac->push = 0x00000003 | dmac->pushdma->start >> 8;
			break;
		default:
			return -EINVAL;
		}
		break;
	default:
		return -EINVAL;
	}

	return 0;
}