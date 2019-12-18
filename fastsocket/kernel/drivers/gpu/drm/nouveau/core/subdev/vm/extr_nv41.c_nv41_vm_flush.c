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
struct nv04_vmmgr_priv {int dummy; } ;
struct nouveau_vm {scalar_t__ vmm; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nv_rd32 (struct nv04_vmmgr_priv*,int) ; 
 TYPE_1__* nv_subdev (struct nv04_vmmgr_priv*) ; 
 int /*<<< orphan*/  nv_wait (struct nv04_vmmgr_priv*,int,int,int) ; 
 int /*<<< orphan*/  nv_warn (struct nv04_vmmgr_priv*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv04_vmmgr_priv*,int,int) ; 

__attribute__((used)) static void
nv41_vm_flush(struct nouveau_vm *vm)
{
	struct nv04_vmmgr_priv *priv = (void *)vm->vmm;

	mutex_lock(&nv_subdev(priv)->mutex);
	nv_wr32(priv, 0x100810, 0x00000022);
	if (!nv_wait(priv, 0x100810, 0x00000020, 0x00000020)) {
		nv_warn(priv, "flush timeout, 0x%08x\n",
			nv_rd32(priv, 0x100810));
	}
	nv_wr32(priv, 0x100810, 0x00000000);
	mutex_unlock(&nv_subdev(priv)->mutex);
}