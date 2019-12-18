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
struct nv10_graph_priv {int dummy; } ;
struct nv10_graph_chan {int dummy; } ;
struct nouveau_object {scalar_t__ parent; } ;

/* Variables and functions */
 int NV10_PGRAPH_DEBUG_4 ; 
 int /*<<< orphan*/  nv04_graph_idle (struct nv10_graph_priv*) ; 
 struct nv10_graph_priv* nv10_graph_priv (struct nv10_graph_chan*) ; 
 int /*<<< orphan*/  nv_mask (struct nv10_graph_priv*,int,int,int) ; 

__attribute__((used)) static int
nv17_graph_mthd_lma_enable(struct nouveau_object *object, u32 mthd,
			   void *args, u32 size)
{
	struct nv10_graph_chan *chan = (void *)object->parent;
	struct nv10_graph_priv *priv = nv10_graph_priv(chan);

	nv04_graph_idle(priv);

	nv_mask(priv, NV10_PGRAPH_DEBUG_4, 0x00000100, 0x00000100);
	nv_mask(priv, 0x4006b0, 0x08000000, 0x08000000);
	return 0;
}