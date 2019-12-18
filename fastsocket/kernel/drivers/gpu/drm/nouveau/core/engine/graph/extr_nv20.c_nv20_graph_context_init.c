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
struct nv20_graph_priv {int /*<<< orphan*/  ctxtab; } ;
struct nv20_graph_chan {int chid; int /*<<< orphan*/  base; } ;
struct nouveau_object {scalar_t__ engine; } ;
struct TYPE_2__ {int addr; } ;

/* Variables and functions */
 int nouveau_graph_context_init (int /*<<< orphan*/ *) ; 
 TYPE_1__* nv_gpuobj (struct nv20_graph_chan*) ; 
 int /*<<< orphan*/  nv_wo32 (int /*<<< orphan*/ ,int,int) ; 

int
nv20_graph_context_init(struct nouveau_object *object)
{
	struct nv20_graph_priv *priv = (void *)object->engine;
	struct nv20_graph_chan *chan = (void *)object;
	int ret;

	ret = nouveau_graph_context_init(&chan->base);
	if (ret)
		return ret;

	nv_wo32(priv->ctxtab, chan->chid * 4, nv_gpuobj(chan)->addr >> 4);
	return 0;
}