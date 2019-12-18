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
struct nvc0_graph_priv {int /*<<< orphan*/  base; int /*<<< orphan*/  unk4188b4; int /*<<< orphan*/  unk4188b8; int /*<<< orphan*/  fuc41ad; int /*<<< orphan*/  fuc41ac; int /*<<< orphan*/  fuc409d; int /*<<< orphan*/  fuc409c; int /*<<< orphan*/  data; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_gpuobj_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_graph_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvc0_graph_dtor_fw (int /*<<< orphan*/ *) ; 

void
nvc0_graph_dtor(struct nouveau_object *object)
{
	struct nvc0_graph_priv *priv = (void *)object;

	kfree(priv->data);

	nvc0_graph_dtor_fw(&priv->fuc409c);
	nvc0_graph_dtor_fw(&priv->fuc409d);
	nvc0_graph_dtor_fw(&priv->fuc41ac);
	nvc0_graph_dtor_fw(&priv->fuc41ad);

	nouveau_gpuobj_ref(NULL, &priv->unk4188b8);
	nouveau_gpuobj_ref(NULL, &priv->unk4188b4);

	nouveau_graph_destroy(&priv->base);
}