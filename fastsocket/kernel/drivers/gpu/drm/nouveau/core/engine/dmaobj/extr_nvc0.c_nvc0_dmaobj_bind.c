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
struct nouveau_object {struct nouveau_dmaobj* parent; } ;
struct nouveau_gpuobj {int dummy; } ;
struct nouveau_dmaobj {int conf0; int target; int access; int /*<<< orphan*/  start; int /*<<< orphan*/  limit; } ;
struct nouveau_dmaeng {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NVA3_DISP_MAST_CLASS 138 
#define  NVA3_DISP_OVLY_CLASS 137 
#define  NVA3_DISP_SYNC_CLASS 136 
 int NVC0_DMA_CONF0_ENABLE ; 
 int NVC0_DMA_CONF0_PRIV ; 
 int NVC0_DMA_CONF0_PRIV_US ; 
 int NVC0_DMA_CONF0_PRIV_VM ; 
 int NVC0_DMA_CONF0_TYPE ; 
 int NVC0_DMA_CONF0_TYPE_LINEAR ; 
 int NVC0_DMA_CONF0_TYPE_VM ; 
 int NVC0_DMA_CONF0_UNKN ; 
 int /*<<< orphan*/  NV_ENGCTX_CLASS ; 
#define  NV_MEM_ACCESS_RO 135 
#define  NV_MEM_ACCESS_RW 134 
#define  NV_MEM_ACCESS_VM 133 
#define  NV_MEM_ACCESS_WO 132 
#define  NV_MEM_TARGET_PCI 131 
#define  NV_MEM_TARGET_PCI_NOSNOOP 130 
#define  NV_MEM_TARGET_VM 129 
#define  NV_MEM_TARGET_VRAM 128 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int nouveau_gpuobj_new (struct nouveau_object*,struct nouveau_object*,int,int,int /*<<< orphan*/ ,struct nouveau_gpuobj**) ; 
 int /*<<< orphan*/  nv_iclass (struct nouveau_object*,int /*<<< orphan*/ ) ; 
 int nv_mclass (struct nouveau_dmaobj*) ; 
 int /*<<< orphan*/  nv_wo32 (struct nouveau_gpuobj*,int,int) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nvc0_dmaobj_bind(struct nouveau_dmaeng *dmaeng,
		 struct nouveau_object *parent,
		 struct nouveau_dmaobj *dmaobj,
		 struct nouveau_gpuobj **pgpuobj)
{
	u32 flags0 = nv_mclass(dmaobj);
	u32 flags5 = 0x00000000;
	int ret;

	if (!nv_iclass(parent, NV_ENGCTX_CLASS)) {
		switch (nv_mclass(parent->parent)) {
		case NVA3_DISP_MAST_CLASS:
		case NVA3_DISP_SYNC_CLASS:
		case NVA3_DISP_OVLY_CLASS:
			break;
		default:
			return -EINVAL;
		}
	} else
		return 0;

	if (!(dmaobj->conf0 & NVC0_DMA_CONF0_ENABLE)) {
		if (dmaobj->target == NV_MEM_TARGET_VM) {
			dmaobj->conf0  = NVC0_DMA_CONF0_PRIV_VM;
			dmaobj->conf0 |= NVC0_DMA_CONF0_TYPE_VM;
		} else {
			dmaobj->conf0  = NVC0_DMA_CONF0_PRIV_US;
			dmaobj->conf0 |= NVC0_DMA_CONF0_TYPE_LINEAR;
			dmaobj->conf0 |= 0x00020000;
		}
	}

	flags0 |= (dmaobj->conf0 & NVC0_DMA_CONF0_TYPE) << 22;
	flags0 |= (dmaobj->conf0 & NVC0_DMA_CONF0_PRIV);
	flags5 |= (dmaobj->conf0 & NVC0_DMA_CONF0_UNKN);

	switch (dmaobj->target) {
	case NV_MEM_TARGET_VM:
		flags0 |= 0x00000000;
		break;
	case NV_MEM_TARGET_VRAM:
		flags0 |= 0x00010000;
		break;
	case NV_MEM_TARGET_PCI:
		flags0 |= 0x00020000;
		break;
	case NV_MEM_TARGET_PCI_NOSNOOP:
		flags0 |= 0x00030000;
		break;
	default:
		return -EINVAL;
	}

	switch (dmaobj->access) {
	case NV_MEM_ACCESS_VM:
		break;
	case NV_MEM_ACCESS_RO:
		flags0 |= 0x00040000;
		break;
	case NV_MEM_ACCESS_WO:
	case NV_MEM_ACCESS_RW:
		flags0 |= 0x00080000;
		break;
	}

	ret = nouveau_gpuobj_new(parent, parent, 24, 32, 0, pgpuobj);
	if (ret == 0) {
		nv_wo32(*pgpuobj, 0x00, flags0);
		nv_wo32(*pgpuobj, 0x04, lower_32_bits(dmaobj->limit));
		nv_wo32(*pgpuobj, 0x08, lower_32_bits(dmaobj->start));
		nv_wo32(*pgpuobj, 0x0c, upper_32_bits(dmaobj->limit) << 24 |
					upper_32_bits(dmaobj->start));
		nv_wo32(*pgpuobj, 0x10, 0x00000000);
		nv_wo32(*pgpuobj, 0x14, flags5);
	}

	return ret;
}