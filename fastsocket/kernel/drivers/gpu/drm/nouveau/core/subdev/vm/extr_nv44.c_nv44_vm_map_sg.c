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
struct nv04_vmmgr_priv {int /*<<< orphan*/  null; } ;
struct nouveau_vma {TYPE_1__* vm; } ;
struct nouveau_mem {int dummy; } ;
struct nouveau_gpuobj {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {scalar_t__ vmm; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv44_vm_fill (struct nouveau_gpuobj*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  nv_wo32 (struct nouveau_gpuobj*,int,int) ; 

__attribute__((used)) static void
nv44_vm_map_sg(struct nouveau_vma *vma, struct nouveau_gpuobj *pgt,
	       struct nouveau_mem *mem, u32 pte, u32 cnt, dma_addr_t *list)
{
	struct nv04_vmmgr_priv *priv = (void *)vma->vm->vmm;
	u32 tmp[4];
	int i;

	if (pte & 3) {
		u32  max = 4 - (pte & 3);
		u32 part = (cnt > max) ? max : cnt;
		nv44_vm_fill(pgt, priv->null, list, pte, part);
		pte  += part;
		list += part;
		cnt  -= part;
	}

	while (cnt >= 4) {
		for (i = 0; i < 4; i++)
			tmp[i] = *list++ >> 12;
		nv_wo32(pgt, pte++ * 4, tmp[0] >>  0 | tmp[1] << 27);
		nv_wo32(pgt, pte++ * 4, tmp[1] >>  5 | tmp[2] << 22);
		nv_wo32(pgt, pte++ * 4, tmp[2] >> 10 | tmp[3] << 17);
		nv_wo32(pgt, pte++ * 4, tmp[3] >> 15 | 0x40000000);
		cnt -= 4;
	}

	if (cnt)
		nv44_vm_fill(pgt, priv->null, list, pte, cnt);
}