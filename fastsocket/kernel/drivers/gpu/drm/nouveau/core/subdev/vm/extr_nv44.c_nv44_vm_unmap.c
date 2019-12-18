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
struct nv04_vmmgr_priv {int /*<<< orphan*/  null; } ;
struct nouveau_gpuobj {int dummy; } ;

/* Variables and functions */
 scalar_t__ nouveau_vmmgr (struct nouveau_gpuobj*) ; 
 int /*<<< orphan*/  nv44_vm_fill (struct nouveau_gpuobj*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  nv_wo32 (struct nouveau_gpuobj*,int,int) ; 

__attribute__((used)) static void
nv44_vm_unmap(struct nouveau_gpuobj *pgt, u32 pte, u32 cnt)
{
	struct nv04_vmmgr_priv *priv = (void *)nouveau_vmmgr(pgt);

	if (pte & 3) {
		u32  max = 4 - (pte & 3);
		u32 part = (cnt > max) ? max : cnt;
		nv44_vm_fill(pgt, priv->null, NULL, pte, part);
		pte  += part;
		cnt  -= part;
	}

	while (cnt >= 4) {
		nv_wo32(pgt, pte++ * 4, 0x00000000);
		nv_wo32(pgt, pte++ * 4, 0x00000000);
		nv_wo32(pgt, pte++ * 4, 0x00000000);
		nv_wo32(pgt, pte++ * 4, 0x00000000);
		cnt -= 4;
	}

	if (cnt)
		nv44_vm_fill(pgt, priv->null, NULL, pte, cnt);
}