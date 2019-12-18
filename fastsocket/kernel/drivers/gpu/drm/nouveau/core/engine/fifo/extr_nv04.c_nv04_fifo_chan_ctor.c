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
typedef  int u32 ;
struct nv04_fifo_priv {int /*<<< orphan*/  ramfc; } ;
struct TYPE_5__ {int chid; TYPE_1__* pushgpu; } ;
struct nv04_fifo_chan {int ramfc; TYPE_2__ base; } ;
struct nv03_channel_dma_class {int offset; int /*<<< orphan*/  pushbuf; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  context_attach; int /*<<< orphan*/  object_detach; int /*<<< orphan*/  object_attach; } ;
struct TYPE_4__ {int addr; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long long NVDEV_ENGINE_DMAOBJ ; 
 unsigned long long NVDEV_ENGINE_GR ; 
 unsigned long long NVDEV_ENGINE_SW ; 
 int NV_PFIFO_CACHE1_BIG_ENDIAN ; 
 int NV_PFIFO_CACHE1_DMA_FETCH_MAX_REQS_8 ; 
 int NV_PFIFO_CACHE1_DMA_FETCH_SIZE_128_BYTES ; 
 int NV_PFIFO_CACHE1_DMA_FETCH_TRIG_128_BYTES ; 
 int nouveau_fifo_channel_create (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,unsigned long long,struct nv04_fifo_chan**) ; 
 int /*<<< orphan*/  nv04_fifo_context_attach ; 
 int /*<<< orphan*/  nv04_fifo_object_attach ; 
 int /*<<< orphan*/  nv04_fifo_object_detach ; 
 struct nouveau_object* nv_object (struct nv04_fifo_chan*) ; 
 TYPE_3__* nv_parent (struct nv04_fifo_chan*) ; 
 int /*<<< orphan*/  nv_wo32 (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
nv04_fifo_chan_ctor(struct nouveau_object *parent,
		    struct nouveau_object *engine,
		    struct nouveau_oclass *oclass, void *data, u32 size,
		    struct nouveau_object **pobject)
{
	struct nv04_fifo_priv *priv = (void *)engine;
	struct nv04_fifo_chan *chan;
	struct nv03_channel_dma_class *args = data;
	int ret;

	if (size < sizeof(*args))
		return -EINVAL;

	ret = nouveau_fifo_channel_create(parent, engine, oclass, 0, 0x800000,
					  0x10000, args->pushbuf,
					  (1ULL << NVDEV_ENGINE_DMAOBJ) |
					  (1ULL << NVDEV_ENGINE_SW) |
					  (1ULL << NVDEV_ENGINE_GR), &chan);
	*pobject = nv_object(chan);
	if (ret)
		return ret;

	nv_parent(chan)->object_attach = nv04_fifo_object_attach;
	nv_parent(chan)->object_detach = nv04_fifo_object_detach;
	nv_parent(chan)->context_attach = nv04_fifo_context_attach;
	chan->ramfc = chan->base.chid * 32;

	nv_wo32(priv->ramfc, chan->ramfc + 0x00, args->offset);
	nv_wo32(priv->ramfc, chan->ramfc + 0x04, args->offset);
	nv_wo32(priv->ramfc, chan->ramfc + 0x08, chan->base.pushgpu->addr >> 4);
	nv_wo32(priv->ramfc, chan->ramfc + 0x10,
			     NV_PFIFO_CACHE1_DMA_FETCH_TRIG_128_BYTES |
			     NV_PFIFO_CACHE1_DMA_FETCH_SIZE_128_BYTES |
#ifdef __BIG_ENDIAN
			     NV_PFIFO_CACHE1_BIG_ENDIAN |
#endif
			     NV_PFIFO_CACHE1_DMA_FETCH_MAX_REQS_8);
	return 0;
}