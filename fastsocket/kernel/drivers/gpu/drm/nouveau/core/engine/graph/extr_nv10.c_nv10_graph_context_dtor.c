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
struct nv10_graph_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/ ** chan; } ;
struct nv10_graph_chan {size_t chid; int /*<<< orphan*/  base; } ;
struct nouveau_object {scalar_t__ engine; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_object_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
nv10_graph_context_dtor(struct nouveau_object *object)
{
	struct nv10_graph_priv *priv = (void *)object->engine;
	struct nv10_graph_chan *chan = (void *)object;
	unsigned long flags;

	spin_lock_irqsave(&priv->lock, flags);
	priv->chan[chan->chid] = NULL;
	spin_unlock_irqrestore(&priv->lock, flags);

	nouveau_object_destroy(&chan->base);
}