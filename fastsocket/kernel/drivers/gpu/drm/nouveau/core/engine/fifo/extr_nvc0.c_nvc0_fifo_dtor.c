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
struct TYPE_2__ {int /*<<< orphan*/  mem; int /*<<< orphan*/  bar; } ;
struct nvc0_fifo_priv {int /*<<< orphan*/  base; int /*<<< orphan*/ * playlist; TYPE_1__ user; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_fifo_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_gpuobj_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_gpuobj_unmap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nvc0_fifo_dtor(struct nouveau_object *object)
{
	struct nvc0_fifo_priv *priv = (void *)object;

	nouveau_gpuobj_unmap(&priv->user.bar);
	nouveau_gpuobj_ref(NULL, &priv->user.mem);
	nouveau_gpuobj_ref(NULL, &priv->playlist[1]);
	nouveau_gpuobj_ref(NULL, &priv->playlist[0]);

	nouveau_fifo_destroy(&priv->base);
}