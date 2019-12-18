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
typedef  int u32 ;
struct pipe_state {int* pipe_0x0200; int* pipe_0x4400; } ;
struct nv10_graph_priv {int dummy; } ;
struct nv10_graph_chan {int* lma_window; struct pipe_state pipe_state; } ;
struct nouveau_object {scalar_t__ parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV10_PGRAPH_PIPE_ADDRESS ; 
 int /*<<< orphan*/  NV10_PGRAPH_PIPE_DATA ; 
 int /*<<< orphan*/  NV10_PGRAPH_XFMODE0 ; 
 int /*<<< orphan*/  NV10_PGRAPH_XFMODE1 ; 
 int /*<<< orphan*/  PIPE_RESTORE (struct nv10_graph_priv*,int*,int) ; 
 int /*<<< orphan*/  PIPE_SAVE (struct nv10_graph_priv*,int*,int) ; 
 int /*<<< orphan*/  nv04_graph_idle (struct nv10_graph_priv*) ; 
 struct nv10_graph_priv* nv10_graph_priv (struct nv10_graph_chan*) ; 
 int nv_rd32 (struct nv10_graph_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv10_graph_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nv17_graph_mthd_lma_window(struct nouveau_object *object, u32 mthd,
			   void *args, u32 size)
{
	struct nv10_graph_chan *chan = (void *)object->parent;
	struct nv10_graph_priv *priv = nv10_graph_priv(chan);
	struct pipe_state *pipe = &chan->pipe_state;
	u32 pipe_0x0040[1], pipe_0x64c0[8], pipe_0x6a80[3], pipe_0x6ab0[3];
	u32 xfmode0, xfmode1;
	u32 data = *(u32 *)args;
	int i;

	chan->lma_window[(mthd - 0x1638) / 4] = data;

	if (mthd != 0x1644)
		return 0;

	nv04_graph_idle(priv);

	PIPE_SAVE(priv, pipe_0x0040, 0x0040);
	PIPE_SAVE(priv, pipe->pipe_0x0200, 0x0200);

	PIPE_RESTORE(priv, chan->lma_window, 0x6790);

	nv04_graph_idle(priv);

	xfmode0 = nv_rd32(priv, NV10_PGRAPH_XFMODE0);
	xfmode1 = nv_rd32(priv, NV10_PGRAPH_XFMODE1);

	PIPE_SAVE(priv, pipe->pipe_0x4400, 0x4400);
	PIPE_SAVE(priv, pipe_0x64c0, 0x64c0);
	PIPE_SAVE(priv, pipe_0x6ab0, 0x6ab0);
	PIPE_SAVE(priv, pipe_0x6a80, 0x6a80);

	nv04_graph_idle(priv);

	nv_wr32(priv, NV10_PGRAPH_XFMODE0, 0x10000000);
	nv_wr32(priv, NV10_PGRAPH_XFMODE1, 0x00000000);
	nv_wr32(priv, NV10_PGRAPH_PIPE_ADDRESS, 0x000064c0);
	for (i = 0; i < 4; i++)
		nv_wr32(priv, NV10_PGRAPH_PIPE_DATA, 0x3f800000);
	for (i = 0; i < 4; i++)
		nv_wr32(priv, NV10_PGRAPH_PIPE_DATA, 0x00000000);

	nv_wr32(priv, NV10_PGRAPH_PIPE_ADDRESS, 0x00006ab0);
	for (i = 0; i < 3; i++)
		nv_wr32(priv, NV10_PGRAPH_PIPE_DATA, 0x3f800000);

	nv_wr32(priv, NV10_PGRAPH_PIPE_ADDRESS, 0x00006a80);
	for (i = 0; i < 3; i++)
		nv_wr32(priv, NV10_PGRAPH_PIPE_DATA, 0x00000000);

	nv_wr32(priv, NV10_PGRAPH_PIPE_ADDRESS, 0x00000040);
	nv_wr32(priv, NV10_PGRAPH_PIPE_DATA, 0x00000008);

	PIPE_RESTORE(priv, pipe->pipe_0x0200, 0x0200);

	nv04_graph_idle(priv);

	PIPE_RESTORE(priv, pipe_0x0040, 0x0040);

	nv_wr32(priv, NV10_PGRAPH_XFMODE0, xfmode0);
	nv_wr32(priv, NV10_PGRAPH_XFMODE1, xfmode1);

	PIPE_RESTORE(priv, pipe_0x64c0, 0x64c0);
	PIPE_RESTORE(priv, pipe_0x6ab0, 0x6ab0);
	PIPE_RESTORE(priv, pipe_0x6a80, 0x6a80);
	PIPE_RESTORE(priv, pipe->pipe_0x4400, 0x4400);

	nv_wr32(priv, NV10_PGRAPH_PIPE_ADDRESS, 0x000000c0);
	nv_wr32(priv, NV10_PGRAPH_PIPE_DATA, 0x00000000);

	nv04_graph_idle(priv);

	return 0;
}