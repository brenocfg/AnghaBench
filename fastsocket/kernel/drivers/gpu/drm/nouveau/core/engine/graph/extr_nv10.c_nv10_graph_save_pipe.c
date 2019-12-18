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
struct pipe_state {int /*<<< orphan*/  pipe_0x0000; int /*<<< orphan*/  pipe_0x0040; int /*<<< orphan*/  pipe_0x7800; int /*<<< orphan*/  pipe_0x7400; int /*<<< orphan*/  pipe_0x7000; int /*<<< orphan*/  pipe_0x6c00; int /*<<< orphan*/  pipe_0x6800; int /*<<< orphan*/  pipe_0x6400; int /*<<< orphan*/  pipe_0x0200; int /*<<< orphan*/  pipe_0x4400; } ;
struct nv10_graph_priv {int dummy; } ;
struct nv10_graph_chan {struct pipe_state pipe_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIPE_SAVE (struct nv10_graph_priv*,int /*<<< orphan*/ ,int) ; 
 struct nv10_graph_priv* nv10_graph_priv (struct nv10_graph_chan*) ; 

__attribute__((used)) static void
nv10_graph_save_pipe(struct nv10_graph_chan *chan)
{
	struct nv10_graph_priv *priv = nv10_graph_priv(chan);
	struct pipe_state *pipe = &chan->pipe_state;

	PIPE_SAVE(priv, pipe->pipe_0x4400, 0x4400);
	PIPE_SAVE(priv, pipe->pipe_0x0200, 0x0200);
	PIPE_SAVE(priv, pipe->pipe_0x6400, 0x6400);
	PIPE_SAVE(priv, pipe->pipe_0x6800, 0x6800);
	PIPE_SAVE(priv, pipe->pipe_0x6c00, 0x6c00);
	PIPE_SAVE(priv, pipe->pipe_0x7000, 0x7000);
	PIPE_SAVE(priv, pipe->pipe_0x7400, 0x7400);
	PIPE_SAVE(priv, pipe->pipe_0x7800, 0x7800);
	PIPE_SAVE(priv, pipe->pipe_0x0040, 0x0040);
	PIPE_SAVE(priv, pipe->pipe_0x0000, 0x0000);
}