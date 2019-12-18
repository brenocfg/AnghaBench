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
struct nv50_bar_priv {int /*<<< orphan*/  base; int /*<<< orphan*/  mem; int /*<<< orphan*/  pad; int /*<<< orphan*/  pgd; TYPE_2__* bar3_vm; int /*<<< orphan*/  bar3; TYPE_2__* bar1_vm; int /*<<< orphan*/  bar1; } ;
struct nouveau_object {int dummy; } ;
struct TYPE_4__ {TYPE_1__* pgt; } ;
struct TYPE_3__ {int /*<<< orphan*/ * obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_bar_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_gpuobj_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_vm_ref (int /*<<< orphan*/ *,TYPE_2__**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nv50_bar_dtor(struct nouveau_object *object)
{
	struct nv50_bar_priv *priv = (void *)object;
	nouveau_gpuobj_ref(NULL, &priv->bar1);
	nouveau_vm_ref(NULL, &priv->bar1_vm, priv->pgd);
	nouveau_gpuobj_ref(NULL, &priv->bar3);
	if (priv->bar3_vm) {
		nouveau_gpuobj_ref(NULL, &priv->bar3_vm->pgt[0].obj[0]);
		nouveau_vm_ref(NULL, &priv->bar3_vm, priv->pgd);
	}
	nouveau_gpuobj_ref(NULL, &priv->pgd);
	nouveau_gpuobj_ref(NULL, &priv->pad);
	nouveau_gpuobj_ref(NULL, &priv->mem);
	nouveau_bar_destroy(&priv->base);
}