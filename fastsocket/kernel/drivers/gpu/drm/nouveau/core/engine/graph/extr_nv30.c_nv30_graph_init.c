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
struct nv20_graph_priv {TYPE_1__* ctxtab; int /*<<< orphan*/  base; } ;
struct nouveau_object {int dummy; } ;
struct TYPE_5__ {int regions; } ;
struct nouveau_fb {TYPE_2__ tile; } ;
struct nouveau_engine {int /*<<< orphan*/  (* tile_prog ) (struct nouveau_engine*,int) ;} ;
struct TYPE_6__ {int chipset; } ;
struct TYPE_4__ {int addr; } ;

/* Variables and functions */
 int NV03_PGRAPH_INTR ; 
 int NV03_PGRAPH_INTR_EN ; 
 int NV04_PGRAPH_DEBUG_0 ; 
 int NV04_PGRAPH_DEBUG_1 ; 
 int NV04_PGRAPH_DEBUG_3 ; 
 int NV04_PGRAPH_LIMIT_VIOL_PIX ; 
 int NV10_PGRAPH_CTX_CONTROL ; 
 int NV10_PGRAPH_DEBUG_4 ; 
 int NV10_PGRAPH_RDI_DATA ; 
 int NV10_PGRAPH_RDI_INDEX ; 
 int NV10_PGRAPH_STATE ; 
 int NV20_PGRAPH_CHANNEL_CTX_TABLE ; 
 struct nouveau_fb* nouveau_fb (struct nouveau_object*) ; 
 int nouveau_graph_init (int /*<<< orphan*/ *) ; 
 TYPE_3__* nv_device (struct nv20_graph_priv*) ; 
 struct nouveau_engine* nv_engine (struct nouveau_object*) ; 
 int nv_rd32 (struct nv20_graph_priv*,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv20_graph_priv*,int,int) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_engine*,int) ; 

int
nv30_graph_init(struct nouveau_object *object)
{
	struct nouveau_engine *engine = nv_engine(object);
	struct nv20_graph_priv *priv = (void *)engine;
	struct nouveau_fb *pfb = nouveau_fb(object);
	int ret, i;

	ret = nouveau_graph_init(&priv->base);
	if (ret)
		return ret;

	nv_wr32(priv, NV20_PGRAPH_CHANNEL_CTX_TABLE, priv->ctxtab->addr >> 4);

	nv_wr32(priv, NV03_PGRAPH_INTR   , 0xFFFFFFFF);
	nv_wr32(priv, NV03_PGRAPH_INTR_EN, 0xFFFFFFFF);

	nv_wr32(priv, NV04_PGRAPH_DEBUG_0, 0xFFFFFFFF);
	nv_wr32(priv, NV04_PGRAPH_DEBUG_0, 0x00000000);
	nv_wr32(priv, NV04_PGRAPH_DEBUG_1, 0x401287c0);
	nv_wr32(priv, 0x400890, 0x01b463ff);
	nv_wr32(priv, NV04_PGRAPH_DEBUG_3, 0xf2de0475);
	nv_wr32(priv, NV10_PGRAPH_DEBUG_4, 0x00008000);
	nv_wr32(priv, NV04_PGRAPH_LIMIT_VIOL_PIX, 0xf04bdff6);
	nv_wr32(priv, 0x400B80, 0x1003d888);
	nv_wr32(priv, 0x400B84, 0x0c000000);
	nv_wr32(priv, 0x400098, 0x00000000);
	nv_wr32(priv, 0x40009C, 0x0005ad00);
	nv_wr32(priv, 0x400B88, 0x62ff00ff); /* suspiciously like PGRAPH_DEBUG_2 */
	nv_wr32(priv, 0x4000a0, 0x00000000);
	nv_wr32(priv, 0x4000a4, 0x00000008);
	nv_wr32(priv, 0x4008a8, 0xb784a400);
	nv_wr32(priv, 0x400ba0, 0x002f8685);
	nv_wr32(priv, 0x400ba4, 0x00231f3f);
	nv_wr32(priv, 0x4008a4, 0x40000020);

	if (nv_device(priv)->chipset == 0x34) {
		nv_wr32(priv, NV10_PGRAPH_RDI_INDEX, 0x00EA0004);
		nv_wr32(priv, NV10_PGRAPH_RDI_DATA , 0x00200201);
		nv_wr32(priv, NV10_PGRAPH_RDI_INDEX, 0x00EA0008);
		nv_wr32(priv, NV10_PGRAPH_RDI_DATA , 0x00000008);
		nv_wr32(priv, NV10_PGRAPH_RDI_INDEX, 0x00EA0000);
		nv_wr32(priv, NV10_PGRAPH_RDI_DATA , 0x00000032);
		nv_wr32(priv, NV10_PGRAPH_RDI_INDEX, 0x00E00004);
		nv_wr32(priv, NV10_PGRAPH_RDI_DATA , 0x00000002);
	}

	nv_wr32(priv, 0x4000c0, 0x00000016);

	/* Turn all the tiling regions off. */
	for (i = 0; i < pfb->tile.regions; i++)
		engine->tile_prog(engine, i);

	nv_wr32(priv, NV10_PGRAPH_CTX_CONTROL, 0x10000100);
	nv_wr32(priv, NV10_PGRAPH_STATE      , 0xFFFFFFFF);
	nv_wr32(priv, 0x0040075c             , 0x00000001);

	/* begin RAM config */
	/* vramsz = pci_resource_len(priv->dev->pdev, 0) - 1; */
	nv_wr32(priv, 0x4009A4, nv_rd32(priv, 0x100200));
	nv_wr32(priv, 0x4009A8, nv_rd32(priv, 0x100204));
	if (nv_device(priv)->chipset != 0x34) {
		nv_wr32(priv, 0x400750, 0x00EA0000);
		nv_wr32(priv, 0x400754, nv_rd32(priv, 0x100200));
		nv_wr32(priv, 0x400750, 0x00EA0004);
		nv_wr32(priv, 0x400754, nv_rd32(priv, 0x100204));
	}
	return 0;
}