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
struct nv20_graph_priv {int /*<<< orphan*/  base; int /*<<< orphan*/  ctxtab; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_gpuobj_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_graph_destroy (int /*<<< orphan*/ *) ; 

void
nv20_graph_dtor(struct nouveau_object *object)
{
	struct nv20_graph_priv *priv = (void *)object;
	nouveau_gpuobj_ref(NULL, &priv->ctxtab);
	nouveau_graph_destroy(&priv->base);
}