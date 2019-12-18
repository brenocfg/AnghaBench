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
struct nouveau_object {int /*<<< orphan*/  parent; } ;
struct nouveau_gpuobj {int dummy; } ;
struct nouveau_dmaobj {int conf0; int target; int start; int limit; } ;
struct nouveau_dmaeng {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NVD0_DISP_MAST_CLASS 134 
#define  NVD0_DISP_OVLY_CLASS 133 
#define  NVD0_DISP_SYNC_CLASS 132 
 int NVD0_DMA_CONF0_ENABLE ; 
 int NVD0_DMA_CONF0_PAGE ; 
 int NVD0_DMA_CONF0_PAGE_LP ; 
 int NVD0_DMA_CONF0_PAGE_SP ; 
 int NVD0_DMA_CONF0_TYPE ; 
 int NVD0_DMA_CONF0_TYPE_LINEAR ; 
 int NVD0_DMA_CONF0_TYPE_VM ; 
#define  NVE0_DISP_MAST_CLASS 131 
#define  NVE0_DISP_OVLY_CLASS 130 
#define  NVE0_DISP_SYNC_CLASS 129 
 int /*<<< orphan*/  NV_ENGCTX_CLASS ; 
 int NV_MEM_TARGET_VM ; 
#define  NV_MEM_TARGET_VRAM 128 
 int nouveau_gpuobj_new (struct nouveau_object*,struct nouveau_object*,int,int,int /*<<< orphan*/ ,struct nouveau_gpuobj**) ; 
 int /*<<< orphan*/  nv_iclass (struct nouveau_object*,int /*<<< orphan*/ ) ; 
 int nv_mclass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_wo32 (struct nouveau_gpuobj*,int,int) ; 

__attribute__((used)) static int
nvd0_dmaobj_bind(struct nouveau_dmaeng *dmaeng,
		 struct nouveau_object *parent,
		 struct nouveau_dmaobj *dmaobj,
		 struct nouveau_gpuobj **pgpuobj)
{
	u32 flags0 = 0x00000000;
	int ret;

	if (!nv_iclass(parent, NV_ENGCTX_CLASS)) {
		switch (nv_mclass(parent->parent)) {
		case NVD0_DISP_MAST_CLASS:
		case NVD0_DISP_SYNC_CLASS:
		case NVD0_DISP_OVLY_CLASS:
		case NVE0_DISP_MAST_CLASS:
		case NVE0_DISP_SYNC_CLASS:
		case NVE0_DISP_OVLY_CLASS:
			break;
		default:
			return -EINVAL;
		}
	} else
		return 0;

	if (!(dmaobj->conf0 & NVD0_DMA_CONF0_ENABLE)) {
		if (dmaobj->target == NV_MEM_TARGET_VM) {
			dmaobj->conf0 |= NVD0_DMA_CONF0_TYPE_VM;
			dmaobj->conf0 |= NVD0_DMA_CONF0_PAGE_LP;
		} else {
			dmaobj->conf0 |= NVD0_DMA_CONF0_TYPE_LINEAR;
			dmaobj->conf0 |= NVD0_DMA_CONF0_PAGE_SP;
		}
	}

	flags0 |= (dmaobj->conf0 & NVD0_DMA_CONF0_TYPE) << 20;
	flags0 |= (dmaobj->conf0 & NVD0_DMA_CONF0_PAGE) >> 4;

	switch (dmaobj->target) {
	case NV_MEM_TARGET_VRAM:
		flags0 |= 0x00000009;
		break;
	default:
		return -EINVAL;
		break;
	}

	ret = nouveau_gpuobj_new(parent, parent, 24, 32, 0, pgpuobj);
	if (ret == 0) {
		nv_wo32(*pgpuobj, 0x00, flags0);
		nv_wo32(*pgpuobj, 0x04, dmaobj->start >> 8);
		nv_wo32(*pgpuobj, 0x08, dmaobj->limit >> 8);
		nv_wo32(*pgpuobj, 0x0c, 0x00000000);
		nv_wo32(*pgpuobj, 0x10, 0x00000000);
		nv_wo32(*pgpuobj, 0x14, 0x00000000);
	}

	return ret;
}