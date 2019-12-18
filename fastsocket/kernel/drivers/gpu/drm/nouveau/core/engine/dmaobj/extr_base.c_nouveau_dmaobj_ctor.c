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
typedef  int u32 ;
struct nv_dma_class {int flags; int /*<<< orphan*/  conf0; int /*<<< orphan*/  limit; int /*<<< orphan*/  start; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct nouveau_gpuobj {int /*<<< orphan*/  conf0; int /*<<< orphan*/  limit; int /*<<< orphan*/  start; int /*<<< orphan*/  access; int /*<<< orphan*/  target; } ;
struct nouveau_dmaobj {int /*<<< orphan*/  conf0; int /*<<< orphan*/  limit; int /*<<< orphan*/  start; int /*<<< orphan*/  access; int /*<<< orphan*/  target; } ;
struct nouveau_dmaeng {int (* bind ) (struct nouveau_dmaeng*,struct nouveau_object*,struct nouveau_gpuobj*,struct nouveau_gpuobj**) ;} ;

/* Variables and functions */
 int EINVAL ; 
#define  NV_DEVICE_CLASS 137 
 int NV_DMA_ACCESS_MASK ; 
#define  NV_DMA_ACCESS_RD 136 
#define  NV_DMA_ACCESS_RDWR 135 
#define  NV_DMA_ACCESS_VM 134 
#define  NV_DMA_ACCESS_WR 133 
#define  NV_DMA_TARGET_AGP 132 
 int NV_DMA_TARGET_MASK ; 
#define  NV_DMA_TARGET_PCI 131 
#define  NV_DMA_TARGET_PCI_US 130 
#define  NV_DMA_TARGET_VM 129 
#define  NV_DMA_TARGET_VRAM 128 
 int /*<<< orphan*/  NV_MEM_ACCESS_RO ; 
 int /*<<< orphan*/  NV_MEM_ACCESS_RW ; 
 int /*<<< orphan*/  NV_MEM_ACCESS_VM ; 
 int /*<<< orphan*/  NV_MEM_ACCESS_WO ; 
 int /*<<< orphan*/  NV_MEM_TARGET_PCI ; 
 int /*<<< orphan*/  NV_MEM_TARGET_PCI_NOSNOOP ; 
 int /*<<< orphan*/  NV_MEM_TARGET_VM ; 
 int /*<<< orphan*/  NV_MEM_TARGET_VRAM ; 
 int nouveau_object_create (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,int /*<<< orphan*/ ,struct nouveau_gpuobj**) ; 
 int /*<<< orphan*/  nouveau_object_ref (int /*<<< orphan*/ *,struct nouveau_object**) ; 
 int nv_mclass (struct nouveau_object*) ; 
 struct nouveau_object* nv_object (struct nouveau_gpuobj*) ; 
 int stub1 (struct nouveau_dmaeng*,struct nouveau_object*,struct nouveau_gpuobj*,struct nouveau_gpuobj**) ; 

__attribute__((used)) static int
nouveau_dmaobj_ctor(struct nouveau_object *parent,
		    struct nouveau_object *engine,
		    struct nouveau_oclass *oclass, void *data, u32 size,
		    struct nouveau_object **pobject)
{
	struct nouveau_dmaeng *dmaeng = (void *)engine;
	struct nouveau_dmaobj *dmaobj;
	struct nouveau_gpuobj *gpuobj;
	struct nv_dma_class *args = data;
	int ret;

	if (size < sizeof(*args))
		return -EINVAL;

	ret = nouveau_object_create(parent, engine, oclass, 0, &dmaobj);
	*pobject = nv_object(dmaobj);
	if (ret)
		return ret;

	switch (args->flags & NV_DMA_TARGET_MASK) {
	case NV_DMA_TARGET_VM:
		dmaobj->target = NV_MEM_TARGET_VM;
		break;
	case NV_DMA_TARGET_VRAM:
		dmaobj->target = NV_MEM_TARGET_VRAM;
		break;
	case NV_DMA_TARGET_PCI:
		dmaobj->target = NV_MEM_TARGET_PCI;
		break;
	case NV_DMA_TARGET_PCI_US:
	case NV_DMA_TARGET_AGP:
		dmaobj->target = NV_MEM_TARGET_PCI_NOSNOOP;
		break;
	default:
		return -EINVAL;
	}

	switch (args->flags & NV_DMA_ACCESS_MASK) {
	case NV_DMA_ACCESS_VM:
		dmaobj->access = NV_MEM_ACCESS_VM;
		break;
	case NV_DMA_ACCESS_RD:
		dmaobj->access = NV_MEM_ACCESS_RO;
		break;
	case NV_DMA_ACCESS_WR:
		dmaobj->access = NV_MEM_ACCESS_WO;
		break;
	case NV_DMA_ACCESS_RDWR:
		dmaobj->access = NV_MEM_ACCESS_RW;
		break;
	default:
		return -EINVAL;
	}

	dmaobj->start = args->start;
	dmaobj->limit = args->limit;
	dmaobj->conf0 = args->conf0;

	switch (nv_mclass(parent)) {
	case NV_DEVICE_CLASS:
		/* delayed, or no, binding */
		break;
	default:
		ret = dmaeng->bind(dmaeng, *pobject, dmaobj, &gpuobj);
		if (ret == 0) {
			nouveau_object_ref(NULL, pobject);
			*pobject = nv_object(gpuobj);
		}
		break;
	}

	return ret;
}