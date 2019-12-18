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
struct TYPE_2__ {int limit; } ;
struct nv04_vmmgr_priv {TYPE_1__ base; } ;
struct nouveau_vm {scalar_t__ vmm; } ;

/* Variables and functions */
 int NV44_GART_PAGE ; 
 int /*<<< orphan*/  nv_error (struct nv04_vmmgr_priv*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_rd32 (struct nv04_vmmgr_priv*,int) ; 
 int /*<<< orphan*/  nv_wait (struct nv04_vmmgr_priv*,int,int,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv04_vmmgr_priv*,int,int) ; 

__attribute__((used)) static void
nv44_vm_flush(struct nouveau_vm *vm)
{
	struct nv04_vmmgr_priv *priv = (void *)vm->vmm;
	nv_wr32(priv, 0x100814, priv->base.limit - NV44_GART_PAGE);
	nv_wr32(priv, 0x100808, 0x00000020);
	if (!nv_wait(priv, 0x100808, 0x00000001, 0x00000001))
		nv_error(priv, "timeout: 0x%08x\n", nv_rd32(priv, 0x100808));
	nv_wr32(priv, 0x100808, 0x00000000);
}