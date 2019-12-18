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
struct pipe_state {int /*<<< orphan*/  pipe_0x0040; int /*<<< orphan*/  pipe_0x0000; int /*<<< orphan*/  pipe_0x4400; int /*<<< orphan*/  pipe_0x7800; int /*<<< orphan*/  pipe_0x7400; int /*<<< orphan*/  pipe_0x7000; int /*<<< orphan*/  pipe_0x6c00; int /*<<< orphan*/  pipe_0x6800; int /*<<< orphan*/  pipe_0x6400; int /*<<< orphan*/  pipe_0x0200; } ;
struct nv10_graph_priv {int dummy; } ;
struct nv10_graph_chan {struct pipe_state pipe_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV10_PGRAPH_PIPE_ADDRESS ; 
 int /*<<< orphan*/  NV10_PGRAPH_PIPE_DATA ; 
 int /*<<< orphan*/  NV10_PGRAPH_XFMODE0 ; 
 int /*<<< orphan*/  NV10_PGRAPH_XFMODE1 ; 
 int /*<<< orphan*/  PIPE_RESTORE (struct nv10_graph_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nv04_graph_idle (struct nv10_graph_priv*) ; 
 struct nv10_graph_priv* nv10_graph_priv (struct nv10_graph_chan*) ; 
 int nv_rd32 (struct nv10_graph_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv10_graph_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
nv10_graph_load_pipe(struct nv10_graph_chan *chan)
{
	struct nv10_graph_priv *priv = nv10_graph_priv(chan);
	struct pipe_state *pipe = &chan->pipe_state;
	u32 xfmode0, xfmode1;
	int i;

	nv04_graph_idle(priv);
	/* XXX check haiku comments */
	xfmode0 = nv_rd32(priv, NV10_PGRAPH_XFMODE0);
	xfmode1 = nv_rd32(priv, NV10_PGRAPH_XFMODE1);
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

	/* restore XFMODE */
	nv_wr32(priv, NV10_PGRAPH_XFMODE0, xfmode0);
	nv_wr32(priv, NV10_PGRAPH_XFMODE1, xfmode1);
	PIPE_RESTORE(priv, pipe->pipe_0x6400, 0x6400);
	PIPE_RESTORE(priv, pipe->pipe_0x6800, 0x6800);
	PIPE_RESTORE(priv, pipe->pipe_0x6c00, 0x6c00);
	PIPE_RESTORE(priv, pipe->pipe_0x7000, 0x7000);
	PIPE_RESTORE(priv, pipe->pipe_0x7400, 0x7400);
	PIPE_RESTORE(priv, pipe->pipe_0x7800, 0x7800);
	PIPE_RESTORE(priv, pipe->pipe_0x4400, 0x4400);
	PIPE_RESTORE(priv, pipe->pipe_0x0000, 0x0000);
	PIPE_RESTORE(priv, pipe->pipe_0x0040, 0x0040);
	nv04_graph_idle(priv);
}