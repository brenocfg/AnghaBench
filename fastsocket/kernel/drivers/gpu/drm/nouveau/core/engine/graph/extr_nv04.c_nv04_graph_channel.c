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
struct nv04_graph_priv {struct nv04_graph_chan** chan; } ;
struct nv04_graph_chan {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct nv04_graph_chan**) ; 
 int /*<<< orphan*/  NV04_PGRAPH_CTX_CONTROL ; 
 int /*<<< orphan*/  NV04_PGRAPH_CTX_USER ; 
 int nv_rd32 (struct nv04_graph_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nv04_graph_chan *
nv04_graph_channel(struct nv04_graph_priv *priv)
{
	struct nv04_graph_chan *chan = NULL;
	if (nv_rd32(priv, NV04_PGRAPH_CTX_CONTROL) & 0x00010000) {
		int chid = nv_rd32(priv, NV04_PGRAPH_CTX_USER) >> 24;
		if (chid < ARRAY_SIZE(priv->chan))
			chan = priv->chan[chid];
	}
	return chan;
}