#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nv20_graph_priv {int dummy; } ;
struct nouveau_fifo {int /*<<< orphan*/  (* start ) (struct nouveau_fifo*,unsigned long*) ;int /*<<< orphan*/  (* pause ) (struct nouveau_fifo*,unsigned long*) ;} ;
struct nouveau_fb_tile {int limit; int pitch; int addr; int zcomp; } ;
struct nouveau_engine {int dummy; } ;
struct TYPE_4__ {struct nouveau_fb_tile* region; } ;
struct TYPE_6__ {TYPE_1__ tile; } ;
struct TYPE_5__ {int chipset; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV10_PGRAPH_RDI_DATA ; 
 int /*<<< orphan*/  NV10_PGRAPH_RDI_INDEX ; 
 int /*<<< orphan*/  NV20_PGRAPH_TILE (int) ; 
 int /*<<< orphan*/  NV20_PGRAPH_TLIMIT (int) ; 
 int /*<<< orphan*/  NV20_PGRAPH_TSIZE (int) ; 
 int /*<<< orphan*/  NV20_PGRAPH_ZCOMP (int) ; 
 TYPE_3__* nouveau_fb (struct nouveau_engine*) ; 
 struct nouveau_fifo* nouveau_fifo (struct nouveau_engine*) ; 
 int /*<<< orphan*/  nv04_graph_idle (struct nv20_graph_priv*) ; 
 TYPE_2__* nv_device (struct nouveau_engine*) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv20_graph_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_fifo*,unsigned long*) ; 
 int /*<<< orphan*/  stub2 (struct nouveau_fifo*,unsigned long*) ; 

void
nv20_graph_tile_prog(struct nouveau_engine *engine, int i)
{
	struct nouveau_fb_tile *tile = &nouveau_fb(engine)->tile.region[i];
	struct nouveau_fifo *pfifo = nouveau_fifo(engine);
	struct nv20_graph_priv *priv = (void *)engine;
	unsigned long flags;

	pfifo->pause(pfifo, &flags);
	nv04_graph_idle(priv);

	nv_wr32(priv, NV20_PGRAPH_TLIMIT(i), tile->limit);
	nv_wr32(priv, NV20_PGRAPH_TSIZE(i), tile->pitch);
	nv_wr32(priv, NV20_PGRAPH_TILE(i), tile->addr);

	nv_wr32(priv, NV10_PGRAPH_RDI_INDEX, 0x00EA0030 + 4 * i);
	nv_wr32(priv, NV10_PGRAPH_RDI_DATA, tile->limit);
	nv_wr32(priv, NV10_PGRAPH_RDI_INDEX, 0x00EA0050 + 4 * i);
	nv_wr32(priv, NV10_PGRAPH_RDI_DATA, tile->pitch);
	nv_wr32(priv, NV10_PGRAPH_RDI_INDEX, 0x00EA0010 + 4 * i);
	nv_wr32(priv, NV10_PGRAPH_RDI_DATA, tile->addr);

	if (nv_device(engine)->chipset != 0x34) {
		nv_wr32(priv, NV20_PGRAPH_ZCOMP(i), tile->zcomp);
		nv_wr32(priv, NV10_PGRAPH_RDI_INDEX, 0x00ea0090 + 4 * i);
		nv_wr32(priv, NV10_PGRAPH_RDI_DATA, tile->zcomp);
	}

	pfifo->start(pfifo, &flags);
}