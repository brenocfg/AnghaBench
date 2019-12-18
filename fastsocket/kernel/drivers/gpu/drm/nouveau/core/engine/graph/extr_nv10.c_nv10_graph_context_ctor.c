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
typedef  int /*<<< orphan*/  u32 ;
struct nv10_graph_priv {int /*<<< orphan*/  lock; struct nv10_graph_chan** chan; } ;
struct nv10_graph_chan {int chid; int /*<<< orphan*/  base; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int /*<<< orphan*/  refcount; } ;
struct nouveau_fifo_chan {size_t chid; } ;
struct TYPE_2__ {int chipset; } ;

/* Variables and functions */
 int NV03_PGRAPH_XY_LOGIC_MISC0 ; 
 int NV10_PGRAPH_CTX_USER ; 
 int NV10_PGRAPH_DEBUG_4 ; 
 int /*<<< orphan*/  NV17_WRITE_CTX (int,int) ; 
 int /*<<< orphan*/  NV_WRITE_CTX (int,int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int nouveau_object_create (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,int /*<<< orphan*/ ,struct nv10_graph_chan**) ; 
 int /*<<< orphan*/  nouveau_object_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nv10_graph_create_pipe (struct nv10_graph_chan*) ; 
 TYPE_1__* nv_device (struct nv10_graph_priv*) ; 
 struct nouveau_object* nv_object (struct nv10_graph_chan*) ; 
 int nv_rd32 (struct nv10_graph_priv*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
nv10_graph_context_ctor(struct nouveau_object *parent,
			struct nouveau_object *engine,
			struct nouveau_oclass *oclass, void *data, u32 size,
			struct nouveau_object **pobject)
{
	struct nouveau_fifo_chan *fifo = (void *)parent;
	struct nv10_graph_priv *priv = (void *)engine;
	struct nv10_graph_chan *chan;
	unsigned long flags;
	int ret;

	ret = nouveau_object_create(parent, engine, oclass, 0, &chan);
	*pobject = nv_object(chan);
	if (ret)
		return ret;

	spin_lock_irqsave(&priv->lock, flags);
	if (priv->chan[fifo->chid]) {
		*pobject = nv_object(priv->chan[fifo->chid]);
		atomic_inc(&(*pobject)->refcount);
		spin_unlock_irqrestore(&priv->lock, flags);
		nouveau_object_destroy(&chan->base);
		return 1;
	}

	NV_WRITE_CTX(0x00400e88, 0x08000000);
	NV_WRITE_CTX(0x00400e9c, 0x4b7fffff);
	NV_WRITE_CTX(NV03_PGRAPH_XY_LOGIC_MISC0, 0x0001ffff);
	NV_WRITE_CTX(0x00400e10, 0x00001000);
	NV_WRITE_CTX(0x00400e14, 0x00001000);
	NV_WRITE_CTX(0x00400e30, 0x00080008);
	NV_WRITE_CTX(0x00400e34, 0x00080008);
	if (nv_device(priv)->chipset >= 0x17) {
		/* is it really needed ??? */
		NV17_WRITE_CTX(NV10_PGRAPH_DEBUG_4,
					nv_rd32(priv, NV10_PGRAPH_DEBUG_4));
		NV17_WRITE_CTX(0x004006b0, nv_rd32(priv, 0x004006b0));
		NV17_WRITE_CTX(0x00400eac, 0x0fff0000);
		NV17_WRITE_CTX(0x00400eb0, 0x0fff0000);
		NV17_WRITE_CTX(0x00400ec0, 0x00000080);
		NV17_WRITE_CTX(0x00400ed0, 0x00000080);
	}
	NV_WRITE_CTX(NV10_PGRAPH_CTX_USER, chan->chid << 24);

	nv10_graph_create_pipe(chan);

	priv->chan[fifo->chid] = chan;
	chan->chid = fifo->chid;
	spin_unlock_irqrestore(&priv->lock, flags);
	return 0;
}