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
typedef  int /*<<< orphan*/  u32 ;
struct nv04_graph_priv {int /*<<< orphan*/  lock; struct nv04_graph_chan** chan; } ;
struct nv04_graph_chan {size_t chid; int /*<<< orphan*/  base; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int /*<<< orphan*/  refcount; } ;
struct nouveau_fifo_chan {size_t chid; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV04_PGRAPH_DEBUG_3 ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int* ctx_reg (struct nv04_graph_chan*,int /*<<< orphan*/ ) ; 
 int nouveau_object_create (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,int /*<<< orphan*/ ,struct nv04_graph_chan**) ; 
 int /*<<< orphan*/  nouveau_object_destroy (int /*<<< orphan*/ *) ; 
 struct nouveau_object* nv_object (struct nv04_graph_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
nv04_graph_context_ctor(struct nouveau_object *parent,
			struct nouveau_object *engine,
			struct nouveau_oclass *oclass, void *data, u32 size,
			struct nouveau_object **pobject)
{
	struct nouveau_fifo_chan *fifo = (void *)parent;
	struct nv04_graph_priv *priv = (void *)engine;
	struct nv04_graph_chan *chan;
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

	*ctx_reg(chan, NV04_PGRAPH_DEBUG_3) = 0xfad4ff31;

	priv->chan[fifo->chid] = chan;
	chan->chid = fifo->chid;
	spin_unlock_irqrestore(&priv->lock, flags);
	return 0;
}