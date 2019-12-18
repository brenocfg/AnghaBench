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
struct nv10_graph_priv {struct nv10_graph_chan** chan; } ;
struct nv10_graph_chan {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct nv10_graph_chan**) ; 
 int nv_rd32 (struct nv10_graph_priv*,int) ; 

__attribute__((used)) static struct nv10_graph_chan *
nv10_graph_channel(struct nv10_graph_priv *priv)
{
	struct nv10_graph_chan *chan = NULL;
	if (nv_rd32(priv, 0x400144) & 0x00010000) {
		int chid = nv_rd32(priv, 0x400148) >> 24;
		if (chid < ARRAY_SIZE(priv->chan))
			chan = priv->chan[chid];
	}
	return chan;
}