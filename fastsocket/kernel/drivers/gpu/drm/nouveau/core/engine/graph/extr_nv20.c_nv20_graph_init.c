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
typedef  int u32 ;
struct nv20_graph_priv {TYPE_1__* ctxtab; int /*<<< orphan*/  base; } ;
struct nouveau_object {int dummy; } ;
struct TYPE_5__ {int regions; } ;
struct nouveau_fb {TYPE_2__ tile; } ;
struct nouveau_engine {int /*<<< orphan*/  (* tile_prog ) (struct nouveau_engine*,int) ;} ;
struct TYPE_6__ {int chipset; int /*<<< orphan*/  pdev; } ;
struct TYPE_4__ {int addr; } ;

/* Variables and functions */
 int NV03_PGRAPH_ABS_UCLIP_XMAX ; 
 int NV03_PGRAPH_ABS_UCLIP_XMIN ; 
 int NV03_PGRAPH_ABS_UCLIP_YMAX ; 
 int NV03_PGRAPH_ABS_UCLIP_YMIN ; 
 int NV03_PGRAPH_INTR ; 
 int NV03_PGRAPH_INTR_EN ; 
 int NV04_PGRAPH_DEBUG_0 ; 
 int NV04_PGRAPH_DEBUG_1 ; 
 int NV04_PGRAPH_DEBUG_3 ; 
 int NV10_PGRAPH_CTX_CONTROL ; 
 int NV10_PGRAPH_DEBUG_4 ; 
 int NV10_PGRAPH_RDI_DATA ; 
 int NV10_PGRAPH_RDI_INDEX ; 
 int NV10_PGRAPH_STATE ; 
 int NV10_PGRAPH_SURFACE ; 
 int NV20_PGRAPH_CHANNEL_CTX_TABLE ; 
 struct nouveau_fb* nouveau_fb (struct nouveau_object*) ; 
 int nouveau_graph_init (int /*<<< orphan*/ *) ; 
 TYPE_3__* nv_device (struct nv20_graph_priv*) ; 
 struct nouveau_engine* nv_engine (struct nouveau_object*) ; 
 int nv_rd32 (struct nv20_graph_priv*,int) ; 
 int /*<<< orphan*/  nv_wait (struct nv20_graph_priv*,int,int,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv20_graph_priv*,int,int) ; 
 int pci_resource_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_engine*,int) ; 

int
nv20_graph_init(struct nouveau_object *object)
{
	struct nouveau_engine *engine = nv_engine(object);
	struct nv20_graph_priv *priv = (void *)engine;
	struct nouveau_fb *pfb = nouveau_fb(object);
	u32 tmp, vramsz;
	int ret, i;

	ret = nouveau_graph_init(&priv->base);
	if (ret)
		return ret;

	nv_wr32(priv, NV20_PGRAPH_CHANNEL_CTX_TABLE, priv->ctxtab->addr >> 4);

	if (nv_device(priv)->chipset == 0x20) {
		nv_wr32(priv, NV10_PGRAPH_RDI_INDEX, 0x003d0000);
		for (i = 0; i < 15; i++)
			nv_wr32(priv, NV10_PGRAPH_RDI_DATA, 0x00000000);
		nv_wait(priv, 0x400700, 0xffffffff, 0x00000000);
	} else {
		nv_wr32(priv, NV10_PGRAPH_RDI_INDEX, 0x02c80000);
		for (i = 0; i < 32; i++)
			nv_wr32(priv, NV10_PGRAPH_RDI_DATA, 0x00000000);
		nv_wait(priv, 0x400700, 0xffffffff, 0x00000000);
	}

	nv_wr32(priv, NV03_PGRAPH_INTR   , 0xFFFFFFFF);
	nv_wr32(priv, NV03_PGRAPH_INTR_EN, 0xFFFFFFFF);

	nv_wr32(priv, NV04_PGRAPH_DEBUG_0, 0xFFFFFFFF);
	nv_wr32(priv, NV04_PGRAPH_DEBUG_0, 0x00000000);
	nv_wr32(priv, NV04_PGRAPH_DEBUG_1, 0x00118700);
	nv_wr32(priv, NV04_PGRAPH_DEBUG_3, 0xF3CE0475); /* 0x4 = auto ctx switch */
	nv_wr32(priv, NV10_PGRAPH_DEBUG_4, 0x00000000);
	nv_wr32(priv, 0x40009C           , 0x00000040);

	if (nv_device(priv)->chipset >= 0x25) {
		nv_wr32(priv, 0x400890, 0x00a8cfff);
		nv_wr32(priv, 0x400610, 0x304B1FB6);
		nv_wr32(priv, 0x400B80, 0x1cbd3883);
		nv_wr32(priv, 0x400B84, 0x44000000);
		nv_wr32(priv, 0x400098, 0x40000080);
		nv_wr32(priv, 0x400B88, 0x000000ff);

	} else {
		nv_wr32(priv, 0x400880, 0x0008c7df);
		nv_wr32(priv, 0x400094, 0x00000005);
		nv_wr32(priv, 0x400B80, 0x45eae20e);
		nv_wr32(priv, 0x400B84, 0x24000000);
		nv_wr32(priv, 0x400098, 0x00000040);
		nv_wr32(priv, NV10_PGRAPH_RDI_INDEX, 0x00E00038);
		nv_wr32(priv, NV10_PGRAPH_RDI_DATA , 0x00000030);
		nv_wr32(priv, NV10_PGRAPH_RDI_INDEX, 0x00E10038);
		nv_wr32(priv, NV10_PGRAPH_RDI_DATA , 0x00000030);
	}

	/* Turn all the tiling regions off. */
	for (i = 0; i < pfb->tile.regions; i++)
		engine->tile_prog(engine, i);

	nv_wr32(priv, 0x4009a0, nv_rd32(priv, 0x100324));
	nv_wr32(priv, NV10_PGRAPH_RDI_INDEX, 0x00EA000C);
	nv_wr32(priv, NV10_PGRAPH_RDI_DATA, nv_rd32(priv, 0x100324));

	nv_wr32(priv, NV10_PGRAPH_CTX_CONTROL, 0x10000100);
	nv_wr32(priv, NV10_PGRAPH_STATE      , 0xFFFFFFFF);

	tmp = nv_rd32(priv, NV10_PGRAPH_SURFACE) & 0x0007ff00;
	nv_wr32(priv, NV10_PGRAPH_SURFACE, tmp);
	tmp = nv_rd32(priv, NV10_PGRAPH_SURFACE) | 0x00020100;
	nv_wr32(priv, NV10_PGRAPH_SURFACE, tmp);

	/* begin RAM config */
	vramsz = pci_resource_len(nv_device(priv)->pdev, 0) - 1;
	nv_wr32(priv, 0x4009A4, nv_rd32(priv, 0x100200));
	nv_wr32(priv, 0x4009A8, nv_rd32(priv, 0x100204));
	nv_wr32(priv, NV10_PGRAPH_RDI_INDEX, 0x00EA0000);
	nv_wr32(priv, NV10_PGRAPH_RDI_DATA , nv_rd32(priv, 0x100200));
	nv_wr32(priv, NV10_PGRAPH_RDI_INDEX, 0x00EA0004);
	nv_wr32(priv, NV10_PGRAPH_RDI_DATA , nv_rd32(priv, 0x100204));
	nv_wr32(priv, 0x400820, 0);
	nv_wr32(priv, 0x400824, 0);
	nv_wr32(priv, 0x400864, vramsz - 1);
	nv_wr32(priv, 0x400868, vramsz - 1);

	/* interesting.. the below overwrites some of the tile setup above.. */
	nv_wr32(priv, 0x400B20, 0x00000000);
	nv_wr32(priv, 0x400B04, 0xFFFFFFFF);

	nv_wr32(priv, NV03_PGRAPH_ABS_UCLIP_XMIN, 0);
	nv_wr32(priv, NV03_PGRAPH_ABS_UCLIP_YMIN, 0);
	nv_wr32(priv, NV03_PGRAPH_ABS_UCLIP_XMAX, 0x7fff);
	nv_wr32(priv, NV03_PGRAPH_ABS_UCLIP_YMAX, 0x7fff);
	return 0;
}