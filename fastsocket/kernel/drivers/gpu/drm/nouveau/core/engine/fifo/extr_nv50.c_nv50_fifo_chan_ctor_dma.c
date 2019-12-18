#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_10__ {TYPE_2__* pushgpu; } ;
struct nv50_fifo_chan {TYPE_7__* ramht; TYPE_3__ base; } ;
struct nv50_fifo_base {int /*<<< orphan*/  ramfc; } ;
struct nv03_channel_dma_class {int /*<<< orphan*/  offset; int /*<<< orphan*/  pushbuf; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct nouveau_bar {int /*<<< orphan*/  (* flush ) (struct nouveau_bar*) ;} ;
struct TYPE_12__ {TYPE_4__* node; } ;
struct TYPE_14__ {int bits; TYPE_5__ base; } ;
struct TYPE_13__ {int /*<<< orphan*/  object_detach; int /*<<< orphan*/  object_attach; int /*<<< orphan*/  context_detach; int /*<<< orphan*/  context_attach; } ;
struct TYPE_11__ {int offset; } ;
struct TYPE_9__ {TYPE_1__* node; } ;
struct TYPE_8__ {int offset; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long long NVDEV_ENGINE_DMAOBJ ; 
 unsigned long long NVDEV_ENGINE_GR ; 
 unsigned long long NVDEV_ENGINE_MPEG ; 
 unsigned long long NVDEV_ENGINE_SW ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 struct nouveau_bar* nouveau_bar (struct nouveau_object*) ; 
 int nouveau_fifo_channel_create (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,unsigned long long,struct nv50_fifo_chan**) ; 
 int nouveau_ramht_new (struct nouveau_object*,struct nouveau_object*,int,int,TYPE_7__**) ; 
 int /*<<< orphan*/  nv50_fifo_context_attach ; 
 int /*<<< orphan*/  nv50_fifo_context_detach ; 
 int /*<<< orphan*/  nv50_fifo_object_attach ; 
 int /*<<< orphan*/  nv50_fifo_object_detach ; 
 struct nouveau_object* nv_object (struct nv50_fifo_chan*) ; 
 TYPE_6__* nv_parent (struct nv50_fifo_chan*) ; 
 int /*<<< orphan*/  nv_wo32 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_bar*) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nv50_fifo_chan_ctor_dma(struct nouveau_object *parent,
			struct nouveau_object *engine,
			struct nouveau_oclass *oclass, void *data, u32 size,
			struct nouveau_object **pobject)
{
	struct nouveau_bar *bar = nouveau_bar(parent);
	struct nv50_fifo_base *base = (void *)parent;
	struct nv50_fifo_chan *chan;
	struct nv03_channel_dma_class *args = data;
	int ret;

	if (size < sizeof(*args))
		return -EINVAL;

	ret = nouveau_fifo_channel_create(parent, engine, oclass, 0, 0xc00000,
					  0x2000, args->pushbuf,
					  (1ULL << NVDEV_ENGINE_DMAOBJ) |
					  (1ULL << NVDEV_ENGINE_SW) |
					  (1ULL << NVDEV_ENGINE_GR) |
					  (1ULL << NVDEV_ENGINE_MPEG), &chan);
	*pobject = nv_object(chan);
	if (ret)
		return ret;

	nv_parent(chan)->context_attach = nv50_fifo_context_attach;
	nv_parent(chan)->context_detach = nv50_fifo_context_detach;
	nv_parent(chan)->object_attach = nv50_fifo_object_attach;
	nv_parent(chan)->object_detach = nv50_fifo_object_detach;

	ret = nouveau_ramht_new(parent, parent, 0x8000, 16, &chan->ramht);
	if (ret)
		return ret;

	nv_wo32(base->ramfc, 0x08, lower_32_bits(args->offset));
	nv_wo32(base->ramfc, 0x0c, upper_32_bits(args->offset));
	nv_wo32(base->ramfc, 0x10, lower_32_bits(args->offset));
	nv_wo32(base->ramfc, 0x14, upper_32_bits(args->offset));
	nv_wo32(base->ramfc, 0x3c, 0x003f6078);
	nv_wo32(base->ramfc, 0x44, 0x01003fff);
	nv_wo32(base->ramfc, 0x48, chan->base.pushgpu->node->offset >> 4);
	nv_wo32(base->ramfc, 0x4c, 0xffffffff);
	nv_wo32(base->ramfc, 0x60, 0x7fffffff);
	nv_wo32(base->ramfc, 0x78, 0x00000000);
	nv_wo32(base->ramfc, 0x7c, 0x30000001);
	nv_wo32(base->ramfc, 0x80, ((chan->ramht->bits - 9) << 27) |
				   (4 << 24) /* SEARCH_FULL */ |
				   (chan->ramht->base.node->offset >> 4));
	bar->flush(bar);
	return 0;
}