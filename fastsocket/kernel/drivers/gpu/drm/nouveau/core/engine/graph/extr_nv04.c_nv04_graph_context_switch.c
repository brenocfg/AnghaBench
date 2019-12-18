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
struct nv04_graph_priv {int /*<<< orphan*/  lock; struct nv04_graph_chan** chan; } ;
struct nv04_graph_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV04_PGRAPH_TRAPPED_ADDR ; 
 struct nv04_graph_chan* nv04_graph_channel (struct nv04_graph_priv*) ; 
 int /*<<< orphan*/  nv04_graph_idle (struct nv04_graph_priv*) ; 
 int /*<<< orphan*/  nv04_graph_load_context (struct nv04_graph_chan*,int) ; 
 int /*<<< orphan*/  nv04_graph_unload_context (struct nv04_graph_chan*) ; 
 int nv_rd32 (struct nv04_graph_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
nv04_graph_context_switch(struct nv04_graph_priv *priv)
{
	struct nv04_graph_chan *prev = NULL;
	struct nv04_graph_chan *next = NULL;
	unsigned long flags;
	int chid;

	spin_lock_irqsave(&priv->lock, flags);
	nv04_graph_idle(priv);

	/* If previous context is valid, we need to save it */
	prev = nv04_graph_channel(priv);
	if (prev)
		nv04_graph_unload_context(prev);

	/* load context for next channel */
	chid = (nv_rd32(priv, NV04_PGRAPH_TRAPPED_ADDR) >> 24) & 0x0f;
	next = priv->chan[chid];
	if (next)
		nv04_graph_load_context(next, chid);

	spin_unlock_irqrestore(&priv->lock, flags);
}