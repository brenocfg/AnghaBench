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
struct TYPE_3__ {int /*<<< orphan*/  mem; int /*<<< orphan*/  bar; } ;
struct nve0_fifo_priv {int /*<<< orphan*/  base; TYPE_2__* engine; TYPE_1__ user; } ;
struct nouveau_object {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * playlist; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  nouveau_fifo_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_gpuobj_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_gpuobj_unmap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nve0_fifo_dtor(struct nouveau_object *object)
{
	struct nve0_fifo_priv *priv = (void *)object;
	int i;

	nouveau_gpuobj_unmap(&priv->user.bar);
	nouveau_gpuobj_ref(NULL, &priv->user.mem);

	for (i = 0; i < ARRAY_SIZE(priv->engine); i++) {
		nouveau_gpuobj_ref(NULL, &priv->engine[i].playlist[1]);
		nouveau_gpuobj_ref(NULL, &priv->engine[i].playlist[0]);
	}

	nouveau_fifo_destroy(&priv->base);
}