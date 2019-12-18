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
struct nv04_instmem_priv {int /*<<< orphan*/  base; scalar_t__ iomem; int /*<<< orphan*/  heap; int /*<<< orphan*/  vbios; int /*<<< orphan*/  ramht; int /*<<< orphan*/  ramro; int /*<<< orphan*/  ramfc; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  nouveau_gpuobj_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_instmem_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_mm_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_ramht_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
nv04_instmem_dtor(struct nouveau_object *object)
{
	struct nv04_instmem_priv *priv = (void *)object;
	nouveau_gpuobj_ref(NULL, &priv->ramfc);
	nouveau_gpuobj_ref(NULL, &priv->ramro);
	nouveau_ramht_ref(NULL, &priv->ramht);
	nouveau_gpuobj_ref(NULL, &priv->vbios);
	nouveau_mm_fini(&priv->heap);
	if (priv->iomem)
		iounmap(priv->iomem);
	nouveau_instmem_destroy(&priv->base);
}