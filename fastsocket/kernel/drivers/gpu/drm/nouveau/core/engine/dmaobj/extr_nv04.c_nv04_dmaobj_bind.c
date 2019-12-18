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
typedef  int u64 ;
typedef  int u32 ;
struct nv04_vmmgr_priv {TYPE_2__* vm; } ;
struct nouveau_object {struct nouveau_dmaobj* parent; } ;
struct nouveau_gpuobj {int dummy; } ;
struct nouveau_dmaobj {int start; int limit; int target; int access; } ;
struct nouveau_dmaeng {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * oclass; } ;
struct TYPE_5__ {TYPE_1__* pgt; } ;
struct TYPE_4__ {struct nouveau_gpuobj** obj; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NV03_CHANNEL_DMA_CLASS 137 
#define  NV10_CHANNEL_DMA_CLASS 136 
#define  NV17_CHANNEL_DMA_CLASS 135 
#define  NV40_CHANNEL_DMA_CLASS 134 
 int /*<<< orphan*/  NV_ENGCTX_CLASS ; 
#define  NV_MEM_ACCESS_RO 133 
#define  NV_MEM_ACCESS_RW 132 
#define  NV_MEM_ACCESS_WO 131 
#define  NV_MEM_TARGET_PCI 130 
#define  NV_MEM_TARGET_PCI_NOSNOOP 129 
 int NV_MEM_TARGET_VM ; 
#define  NV_MEM_TARGET_VRAM 128 
 int nouveau_gpuobj_dup (struct nouveau_object*,struct nouveau_gpuobj*,struct nouveau_gpuobj**) ; 
 int nouveau_gpuobj_new (struct nouveau_object*,struct nouveau_object*,int,int,int /*<<< orphan*/ ,struct nouveau_gpuobj**) ; 
 struct nv04_vmmgr_priv* nv04_vmmgr (struct nouveau_dmaeng*) ; 
 int /*<<< orphan*/  nv04_vmmgr_oclass ; 
 int /*<<< orphan*/  nv_iclass (struct nouveau_object*,int /*<<< orphan*/ ) ; 
 int nv_mclass (struct nouveau_dmaobj*) ; 
 TYPE_3__* nv_object (struct nv04_vmmgr_priv*) ; 
 int nv_ro32 (struct nouveau_gpuobj*,int) ; 
 int /*<<< orphan*/  nv_wo32 (struct nouveau_gpuobj*,int,int) ; 

__attribute__((used)) static int
nv04_dmaobj_bind(struct nouveau_dmaeng *dmaeng,
		 struct nouveau_object *parent,
		 struct nouveau_dmaobj *dmaobj,
		 struct nouveau_gpuobj **pgpuobj)
{
	struct nv04_vmmgr_priv *vmm = nv04_vmmgr(dmaeng);
	struct nouveau_gpuobj *gpuobj;
	u32 flags0 = nv_mclass(dmaobj);
	u32 flags2 = 0x00000000;
	u64 offset = dmaobj->start & 0xfffff000;
	u64 adjust = dmaobj->start & 0x00000fff;
	u32 length = dmaobj->limit - dmaobj->start;
	int ret;

	if (!nv_iclass(parent, NV_ENGCTX_CLASS)) {
		switch (nv_mclass(parent->parent)) {
		case NV03_CHANNEL_DMA_CLASS:
		case NV10_CHANNEL_DMA_CLASS:
		case NV17_CHANNEL_DMA_CLASS:
		case NV40_CHANNEL_DMA_CLASS:
			break;
		default:
			return -EINVAL;
		}
	}

	if (dmaobj->target == NV_MEM_TARGET_VM) {
		if (nv_object(vmm)->oclass == &nv04_vmmgr_oclass) {
			struct nouveau_gpuobj *pgt = vmm->vm->pgt[0].obj[0];
			if (!dmaobj->start)
				return nouveau_gpuobj_dup(parent, pgt, pgpuobj);
			offset  = nv_ro32(pgt, 8 + (offset >> 10));
			offset &= 0xfffff000;
		}

		dmaobj->target = NV_MEM_TARGET_PCI;
		dmaobj->access = NV_MEM_ACCESS_RW;
	}

	switch (dmaobj->target) {
	case NV_MEM_TARGET_VRAM:
		flags0 |= 0x00003000;
		break;
	case NV_MEM_TARGET_PCI:
		flags0 |= 0x00023000;
		break;
	case NV_MEM_TARGET_PCI_NOSNOOP:
		flags0 |= 0x00033000;
		break;
	default:
		return -EINVAL;
	}

	switch (dmaobj->access) {
	case NV_MEM_ACCESS_RO:
		flags0 |= 0x00004000;
		break;
	case NV_MEM_ACCESS_WO:
		flags0 |= 0x00008000;
	case NV_MEM_ACCESS_RW:
		flags2 |= 0x00000002;
		break;
	default:
		return -EINVAL;
	}

	ret = nouveau_gpuobj_new(parent, parent, 16, 16, 0, &gpuobj);
	*pgpuobj = gpuobj;
	if (ret == 0) {
		nv_wo32(*pgpuobj, 0x00, flags0 | (adjust << 20));
		nv_wo32(*pgpuobj, 0x04, length);
		nv_wo32(*pgpuobj, 0x08, flags2 | offset);
		nv_wo32(*pgpuobj, 0x0c, flags2 | offset);
	}

	return ret;
}