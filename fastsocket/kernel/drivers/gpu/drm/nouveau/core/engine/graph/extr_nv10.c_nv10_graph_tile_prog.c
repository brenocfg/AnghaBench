#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nv10_graph_priv {int dummy; } ;
struct nouveau_fifo {int /*<<< orphan*/  (* start ) (struct nouveau_fifo*,unsigned long*) ;int /*<<< orphan*/  (* pause ) (struct nouveau_fifo*,unsigned long*) ;} ;
struct nouveau_fb_tile {int /*<<< orphan*/  addr; int /*<<< orphan*/  pitch; int /*<<< orphan*/  limit; } ;
struct nouveau_engine {int dummy; } ;
struct TYPE_3__ {struct nouveau_fb_tile* region; } ;
struct TYPE_4__ {TYPE_1__ tile; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV10_PGRAPH_TILE (int) ; 
 int /*<<< orphan*/  NV10_PGRAPH_TLIMIT (int) ; 
 int /*<<< orphan*/  NV10_PGRAPH_TSIZE (int) ; 
 TYPE_2__* nouveau_fb (struct nouveau_engine*) ; 
 struct nouveau_fifo* nouveau_fifo (struct nouveau_engine*) ; 
 int /*<<< orphan*/  nv04_graph_idle (struct nv10_graph_priv*) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv10_graph_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_fifo*,unsigned long*) ; 
 int /*<<< orphan*/  stub2 (struct nouveau_fifo*,unsigned long*) ; 

__attribute__((used)) static void
nv10_graph_tile_prog(struct nouveau_engine *engine, int i)
{
	struct nouveau_fb_tile *tile = &nouveau_fb(engine)->tile.region[i];
	struct nouveau_fifo *pfifo = nouveau_fifo(engine);
	struct nv10_graph_priv *priv = (void *)engine;
	unsigned long flags;

	pfifo->pause(pfifo, &flags);
	nv04_graph_idle(priv);

	nv_wr32(priv, NV10_PGRAPH_TLIMIT(i), tile->limit);
	nv_wr32(priv, NV10_PGRAPH_TSIZE(i), tile->pitch);
	nv_wr32(priv, NV10_PGRAPH_TILE(i), tile->addr);

	pfifo->start(pfifo, &flags);
}