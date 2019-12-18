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
struct nv04_graph_priv {int /*<<< orphan*/  lock; } ;
struct nv04_graph_chan {int /*<<< orphan*/  base; } ;
struct nouveau_object {scalar_t__ engine; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV04_PGRAPH_FIFO ; 
 int nouveau_object_fini (int /*<<< orphan*/ *,int) ; 
 struct nv04_graph_chan* nv04_graph_channel (struct nv04_graph_priv*) ; 
 int /*<<< orphan*/  nv04_graph_unload_context (struct nv04_graph_chan*) ; 
 int /*<<< orphan*/  nv_mask (struct nv04_graph_priv*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
nv04_graph_context_fini(struct nouveau_object *object, bool suspend)
{
	struct nv04_graph_priv *priv = (void *)object->engine;
	struct nv04_graph_chan *chan = (void *)object;
	unsigned long flags;

	spin_lock_irqsave(&priv->lock, flags);
	nv_mask(priv, NV04_PGRAPH_FIFO, 0x00000001, 0x00000000);
	if (nv04_graph_channel(priv) == chan)
		nv04_graph_unload_context(chan);
	nv_mask(priv, NV04_PGRAPH_FIFO, 0x00000001, 0x00000001);
	spin_unlock_irqrestore(&priv->lock, flags);

	return nouveau_object_fini(&chan->base, suspend);
}