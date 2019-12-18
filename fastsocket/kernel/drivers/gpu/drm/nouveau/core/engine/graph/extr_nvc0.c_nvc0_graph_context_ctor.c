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
typedef  int u64 ;
typedef  int u32 ;
struct nvc0_graph_priv {int size; int* data; int /*<<< orphan*/  firmware; struct nvc0_graph_mmio* mmio_list; struct nvc0_graph_mmio* mmio_data; } ;
struct nvc0_graph_mmio {int size; int align; int access; int addr; int data; int shift; size_t buffer; } ;
struct nvc0_graph_data {int size; int align; int access; int addr; int data; int shift; size_t buffer; } ;
struct TYPE_5__ {int offset; } ;
struct nvc0_graph_chan {int mmio_nr; TYPE_2__ mmio_vma; struct nvc0_graph_chan* mmio; TYPE_1__* data; } ;
struct nouveau_vm {int dummy; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct TYPE_6__ {struct nouveau_vm* vm; } ;
struct TYPE_4__ {TYPE_2__ vma; struct nvc0_graph_chan* mem; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct nvc0_graph_mmio*) ; 
 int /*<<< orphan*/  NVOBJ_FLAG_ZERO_ALLOC ; 
 int NV_MEM_ACCESS_RW ; 
 int NV_MEM_ACCESS_SYS ; 
 int lower_32_bits (int) ; 
 TYPE_3__* nouveau_client (struct nouveau_object*) ; 
 int nouveau_gpuobj_map_vm (struct nvc0_graph_chan*,struct nouveau_vm*,int,TYPE_2__*) ; 
 int nouveau_gpuobj_new (struct nouveau_object*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,struct nvc0_graph_chan**) ; 
 int nouveau_graph_context_create (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,struct nvc0_graph_chan**) ; 
 struct nvc0_graph_chan* nv_gpuobj (struct nvc0_graph_chan*) ; 
 struct nouveau_object* nv_object (struct nvc0_graph_chan*) ; 
 int /*<<< orphan*/  nv_wo32 (struct nvc0_graph_chan*,int,int) ; 
 int upper_32_bits (int) ; 

int
nvc0_graph_context_ctor(struct nouveau_object *parent,
			struct nouveau_object *engine,
			struct nouveau_oclass *oclass, void *args, u32 size,
			struct nouveau_object **pobject)
{
	struct nouveau_vm *vm = nouveau_client(parent)->vm;
	struct nvc0_graph_priv *priv = (void *)engine;
	struct nvc0_graph_data *data = priv->mmio_data;
	struct nvc0_graph_mmio *mmio = priv->mmio_list;
	struct nvc0_graph_chan *chan;
	int ret, i;

	/* allocate memory for context, and fill with default values */
	ret = nouveau_graph_context_create(parent, engine, oclass, NULL,
					   priv->size, 0x100,
					   NVOBJ_FLAG_ZERO_ALLOC, &chan);
	*pobject = nv_object(chan);
	if (ret)
		return ret;

	/* allocate memory for a "mmio list" buffer that's used by the HUB
	 * fuc to modify some per-context register settings on first load
	 * of the context.
	 */
	ret = nouveau_gpuobj_new(parent, NULL, 0x1000, 0x100, 0, &chan->mmio);
	if (ret)
		return ret;

	ret = nouveau_gpuobj_map_vm(nv_gpuobj(chan->mmio), vm,
				    NV_MEM_ACCESS_RW | NV_MEM_ACCESS_SYS,
				    &chan->mmio_vma);
	if (ret)
		return ret;

	/* allocate buffers referenced by mmio list */
	for (i = 0; data->size && i < ARRAY_SIZE(priv->mmio_data); i++) {
		ret = nouveau_gpuobj_new(parent, NULL, data->size, data->align,
					 0, &chan->data[i].mem);
		if (ret)
			return ret;

		ret = nouveau_gpuobj_map_vm(chan->data[i].mem, vm, data->access,
					   &chan->data[i].vma);
		if (ret)
			return ret;

		data++;
	}

	/* finally, fill in the mmio list and point the context at it */
	for (i = 0; mmio->addr && i < ARRAY_SIZE(priv->mmio_list); i++) {
		u32 addr = mmio->addr;
		u32 data = mmio->data;

		if (mmio->shift) {
			u64 info = chan->data[mmio->buffer].vma.offset;
			data |= info >> mmio->shift;
		}

		nv_wo32(chan->mmio, chan->mmio_nr++ * 4, addr);
		nv_wo32(chan->mmio, chan->mmio_nr++ * 4, data);
		mmio++;
	}

	for (i = 0; i < priv->size; i += 4)
		nv_wo32(chan, i, priv->data[i / 4]);

	if (!priv->firmware) {
		nv_wo32(chan, 0x00, chan->mmio_nr / 2);
		nv_wo32(chan, 0x04, chan->mmio_vma.offset >> 8);
	} else {
		nv_wo32(chan, 0xf4, 0);
		nv_wo32(chan, 0xf8, 0);
		nv_wo32(chan, 0x10, chan->mmio_nr / 2);
		nv_wo32(chan, 0x14, lower_32_bits(chan->mmio_vma.offset));
		nv_wo32(chan, 0x18, upper_32_bits(chan->mmio_vma.offset));
		nv_wo32(chan, 0x1c, 1);
		nv_wo32(chan, 0x20, 0);
		nv_wo32(chan, 0x28, 0);
		nv_wo32(chan, 0x2c, 0);
	}

	return 0;
}