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
struct nv04_vmmgr_priv {int /*<<< orphan*/  base; int /*<<< orphan*/  null; scalar_t__ nullp; TYPE_3__* vm; } ;
struct nouveau_object {int dummy; } ;
struct TYPE_6__ {TYPE_1__* pgt; } ;
struct TYPE_5__ {int /*<<< orphan*/  pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_gpuobj_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_vm_ref (int /*<<< orphan*/ *,TYPE_3__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_vmmgr_destroy (int /*<<< orphan*/ *) ; 
 TYPE_2__* nv_device (struct nv04_vmmgr_priv*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 

void
nv04_vmmgr_dtor(struct nouveau_object *object)
{
	struct nv04_vmmgr_priv *priv = (void *)object;
	if (priv->vm) {
		nouveau_gpuobj_ref(NULL, &priv->vm->pgt[0].obj[0]);
		nouveau_vm_ref(NULL, &priv->vm, NULL);
	}
	if (priv->nullp) {
		pci_free_consistent(nv_device(priv)->pdev, 16 * 1024,
				    priv->nullp, priv->null);
	}
	nouveau_vmmgr_destroy(&priv->base);
}