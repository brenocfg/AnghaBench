#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nv04_vmmgr_priv {int null; int /*<<< orphan*/  base; TYPE_2__* vm; } ;
struct nouveau_object {int dummy; } ;
struct nouveau_gpuobj {int addr; } ;
struct TYPE_4__ {TYPE_1__* pgt; } ;
struct TYPE_3__ {struct nouveau_gpuobj** obj; } ;

/* Variables and functions */
 int NV44_GART_SIZE ; 
 int nouveau_vmmgr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nv_mask (struct nv04_vmmgr_priv*,int,int,int) ; 
 int nv_rd32 (struct nv04_vmmgr_priv*,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv04_vmmgr_priv*,int,int) ; 

__attribute__((used)) static int
nv44_vmmgr_init(struct nouveau_object *object)
{
	struct nv04_vmmgr_priv *priv = (void *)object;
	struct nouveau_gpuobj *gart = priv->vm->pgt[0].obj[0];
	u32 addr;
	int ret;

	ret = nouveau_vmmgr_init(&priv->base);
	if (ret)
		return ret;

	/* calculate vram address of this PRAMIN block, object must be
	 * allocated on 512KiB alignment, and not exceed a total size
	 * of 512KiB for this to work correctly
	 */
	addr  = nv_rd32(priv, 0x10020c);
	addr -= ((gart->addr >> 19) + 1) << 19;

	nv_wr32(priv, 0x100850, 0x80000000);
	nv_wr32(priv, 0x100818, priv->null);
	nv_wr32(priv, 0x100804, NV44_GART_SIZE);
	nv_wr32(priv, 0x100850, 0x00008000);
	nv_mask(priv, 0x10008c, 0x00000200, 0x00000200);
	nv_wr32(priv, 0x100820, 0x00000000);
	nv_wr32(priv, 0x10082c, 0x00000001);
	nv_wr32(priv, 0x100800, addr | 0x00000010);
	return 0;
}