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
struct nvc0_graph_chan {int /*<<< orphan*/  base; int /*<<< orphan*/  mmio; int /*<<< orphan*/  mmio_vma; TYPE_1__* data; } ;
struct nouveau_object {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mem; int /*<<< orphan*/  vma; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  nouveau_gpuobj_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_gpuobj_unmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_graph_context_destroy (int /*<<< orphan*/ *) ; 

void
nvc0_graph_context_dtor(struct nouveau_object *object)
{
	struct nvc0_graph_chan *chan = (void *)object;
	int i;

	for (i = 0; i < ARRAY_SIZE(chan->data); i++) {
		nouveau_gpuobj_unmap(&chan->data[i].vma);
		nouveau_gpuobj_ref(NULL, &chan->data[i].mem);
	}

	nouveau_gpuobj_unmap(&chan->mmio_vma);
	nouveau_gpuobj_ref(NULL, &chan->mmio);

	nouveau_graph_context_destroy(&chan->base);
}