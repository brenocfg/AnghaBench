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
struct nv40_graph_priv {int dummy; } ;
struct nouveau_fifo {int /*<<< orphan*/  (* start ) (struct nouveau_fifo*,unsigned long*) ;int /*<<< orphan*/  (* pause ) (struct nouveau_fifo*,unsigned long*) ;} ;
struct nouveau_fb_tile {int /*<<< orphan*/  zcomp; int /*<<< orphan*/  addr; int /*<<< orphan*/  limit; int /*<<< orphan*/  pitch; } ;
struct nouveau_engine {int dummy; } ;
struct TYPE_4__ {struct nouveau_fb_tile* region; } ;
struct TYPE_6__ {TYPE_1__ tile; } ;
struct TYPE_5__ {int chipset; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV20_PGRAPH_TILE (int) ; 
 int /*<<< orphan*/  NV20_PGRAPH_TLIMIT (int) ; 
 int /*<<< orphan*/  NV20_PGRAPH_TSIZE (int) ; 
 int /*<<< orphan*/  NV20_PGRAPH_ZCOMP (int) ; 
 int /*<<< orphan*/  NV40_PGRAPH_TILE1 (int) ; 
 int /*<<< orphan*/  NV40_PGRAPH_TLIMIT1 (int) ; 
 int /*<<< orphan*/  NV40_PGRAPH_TSIZE1 (int) ; 
 int /*<<< orphan*/  NV40_PGRAPH_ZCOMP1 (int) ; 
 int /*<<< orphan*/  NV41_PGRAPH_ZCOMP0 (int) ; 
 int /*<<< orphan*/  NV41_PGRAPH_ZCOMP1 (int) ; 
 int /*<<< orphan*/  NV47_PGRAPH_TILE (int) ; 
 int /*<<< orphan*/  NV47_PGRAPH_TLIMIT (int) ; 
 int /*<<< orphan*/  NV47_PGRAPH_TSIZE (int) ; 
 int /*<<< orphan*/  NV47_PGRAPH_ZCOMP0 (int) ; 
 int /*<<< orphan*/  NV47_PGRAPH_ZCOMP1 (int) ; 
 TYPE_3__* nouveau_fb (struct nouveau_engine*) ; 
 struct nouveau_fifo* nouveau_fifo (struct nouveau_engine*) ; 
 int /*<<< orphan*/  nv04_graph_idle (struct nv40_graph_priv*) ; 
 TYPE_2__* nv_device (struct nv40_graph_priv*) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv40_graph_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_fifo*,unsigned long*) ; 
 int /*<<< orphan*/  stub2 (struct nouveau_fifo*,unsigned long*) ; 

__attribute__((used)) static void
nv40_graph_tile_prog(struct nouveau_engine *engine, int i)
{
	struct nouveau_fb_tile *tile = &nouveau_fb(engine)->tile.region[i];
	struct nouveau_fifo *pfifo = nouveau_fifo(engine);
	struct nv40_graph_priv *priv = (void *)engine;
	unsigned long flags;

	pfifo->pause(pfifo, &flags);
	nv04_graph_idle(priv);

	switch (nv_device(priv)->chipset) {
	case 0x40:
	case 0x41:
	case 0x42:
	case 0x43:
	case 0x45:
	case 0x4e:
		nv_wr32(priv, NV20_PGRAPH_TSIZE(i), tile->pitch);
		nv_wr32(priv, NV20_PGRAPH_TLIMIT(i), tile->limit);
		nv_wr32(priv, NV20_PGRAPH_TILE(i), tile->addr);
		nv_wr32(priv, NV40_PGRAPH_TSIZE1(i), tile->pitch);
		nv_wr32(priv, NV40_PGRAPH_TLIMIT1(i), tile->limit);
		nv_wr32(priv, NV40_PGRAPH_TILE1(i), tile->addr);
		switch (nv_device(priv)->chipset) {
		case 0x40:
		case 0x45:
			nv_wr32(priv, NV20_PGRAPH_ZCOMP(i), tile->zcomp);
			nv_wr32(priv, NV40_PGRAPH_ZCOMP1(i), tile->zcomp);
			break;
		case 0x41:
		case 0x42:
		case 0x43:
			nv_wr32(priv, NV41_PGRAPH_ZCOMP0(i), tile->zcomp);
			nv_wr32(priv, NV41_PGRAPH_ZCOMP1(i), tile->zcomp);
			break;
		default:
			break;
		}
		break;
	case 0x44:
	case 0x4a:
		nv_wr32(priv, NV20_PGRAPH_TSIZE(i), tile->pitch);
		nv_wr32(priv, NV20_PGRAPH_TLIMIT(i), tile->limit);
		nv_wr32(priv, NV20_PGRAPH_TILE(i), tile->addr);
		break;
	case 0x46:
	case 0x4c:
	case 0x47:
	case 0x49:
	case 0x4b:
	case 0x63:
	case 0x67:
	case 0x68:
		nv_wr32(priv, NV47_PGRAPH_TSIZE(i), tile->pitch);
		nv_wr32(priv, NV47_PGRAPH_TLIMIT(i), tile->limit);
		nv_wr32(priv, NV47_PGRAPH_TILE(i), tile->addr);
		nv_wr32(priv, NV40_PGRAPH_TSIZE1(i), tile->pitch);
		nv_wr32(priv, NV40_PGRAPH_TLIMIT1(i), tile->limit);
		nv_wr32(priv, NV40_PGRAPH_TILE1(i), tile->addr);
		switch (nv_device(priv)->chipset) {
		case 0x47:
		case 0x49:
		case 0x4b:
			nv_wr32(priv, NV47_PGRAPH_ZCOMP0(i), tile->zcomp);
			nv_wr32(priv, NV47_PGRAPH_ZCOMP1(i), tile->zcomp);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	pfifo->start(pfifo, &flags);
}