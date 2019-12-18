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
struct nvc0_bar_priv {int /*<<< orphan*/  base; TYPE_2__* bar; } ;
struct nouveau_object {int dummy; } ;
struct TYPE_6__ {TYPE_1__* pgt; } ;
struct TYPE_5__ {int /*<<< orphan*/  mem; int /*<<< orphan*/  pgd; TYPE_3__* vm; } ;
struct TYPE_4__ {int /*<<< orphan*/ * obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_bar_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_gpuobj_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_vm_ref (int /*<<< orphan*/ *,TYPE_3__**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nvc0_bar_dtor(struct nouveau_object *object)
{
	struct nvc0_bar_priv *priv = (void *)object;

	nouveau_vm_ref(NULL, &priv->bar[1].vm, priv->bar[1].pgd);
	nouveau_gpuobj_ref(NULL, &priv->bar[1].pgd);
	nouveau_gpuobj_ref(NULL, &priv->bar[1].mem);

	if (priv->bar[0].vm) {
		nouveau_gpuobj_ref(NULL, &priv->bar[0].vm->pgt[0].obj[0]);
		nouveau_vm_ref(NULL, &priv->bar[0].vm, priv->bar[0].pgd);
	}
	nouveau_gpuobj_ref(NULL, &priv->bar[0].pgd);
	nouveau_gpuobj_ref(NULL, &priv->bar[0].mem);

	nouveau_bar_destroy(&priv->base);
}