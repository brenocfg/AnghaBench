#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nv40_graph_priv {int /*<<< orphan*/  size; int /*<<< orphan*/  base; } ;
struct nouveau_object {int dummy; } ;
struct TYPE_4__ {int regions; } ;
struct nouveau_fb {TYPE_1__ tile; } ;
struct nouveau_engine {int /*<<< orphan*/  (* tile_prog ) (struct nouveau_engine*,int) ;} ;
struct TYPE_5__ {int chipset; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int NV03_PGRAPH_INTR ; 
 int NV04_PGRAPH_DEBUG_0 ; 
 int NV04_PGRAPH_DEBUG_1 ; 
 int NV04_PGRAPH_DEBUG_3 ; 
 int NV04_PGRAPH_LIMIT_VIOL_PIX ; 
 int NV10_PGRAPH_CTX_CONTROL ; 
 int NV10_PGRAPH_DEBUG_4 ; 
 int NV10_PGRAPH_STATE ; 
 int NV40_PGRAPH_CTXCTL_CUR ; 
 int NV40_PGRAPH_INTR_EN ; 
 struct nouveau_fb* nouveau_fb (struct nouveau_object*) ; 
 int nouveau_graph_init (int /*<<< orphan*/ *) ; 
 int nv40_grctx_init (TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* nv_device (struct nv40_graph_priv*) ; 
 struct nouveau_engine* nv_engine (struct nouveau_object*) ; 
 int nv_rd32 (struct nv40_graph_priv*,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv40_graph_priv*,int,int) ; 
 int pci_resource_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_engine*,int) ; 

__attribute__((used)) static int
nv40_graph_init(struct nouveau_object *object)
{
	struct nouveau_engine *engine = nv_engine(object);
	struct nouveau_fb *pfb = nouveau_fb(object);
	struct nv40_graph_priv *priv = (void *)engine;
	int ret, i, j;
	u32 vramsz;

	ret = nouveau_graph_init(&priv->base);
	if (ret)
		return ret;

	/* generate and upload context program */
	ret = nv40_grctx_init(nv_device(priv), &priv->size);
	if (ret)
		return ret;

	/* No context present currently */
	nv_wr32(priv, NV40_PGRAPH_CTXCTL_CUR, 0x00000000);

	nv_wr32(priv, NV03_PGRAPH_INTR   , 0xFFFFFFFF);
	nv_wr32(priv, NV40_PGRAPH_INTR_EN, 0xFFFFFFFF);

	nv_wr32(priv, NV04_PGRAPH_DEBUG_0, 0xFFFFFFFF);
	nv_wr32(priv, NV04_PGRAPH_DEBUG_0, 0x00000000);
	nv_wr32(priv, NV04_PGRAPH_DEBUG_1, 0x401287c0);
	nv_wr32(priv, NV04_PGRAPH_DEBUG_3, 0xe0de8055);
	nv_wr32(priv, NV10_PGRAPH_DEBUG_4, 0x00008000);
	nv_wr32(priv, NV04_PGRAPH_LIMIT_VIOL_PIX, 0x00be3c5f);

	nv_wr32(priv, NV10_PGRAPH_CTX_CONTROL, 0x10010100);
	nv_wr32(priv, NV10_PGRAPH_STATE      , 0xFFFFFFFF);

	j = nv_rd32(priv, 0x1540) & 0xff;
	if (j) {
		for (i = 0; !(j & 1); j >>= 1, i++)
			;
		nv_wr32(priv, 0x405000, i);
	}

	if (nv_device(priv)->chipset == 0x40) {
		nv_wr32(priv, 0x4009b0, 0x83280fff);
		nv_wr32(priv, 0x4009b4, 0x000000a0);
	} else {
		nv_wr32(priv, 0x400820, 0x83280eff);
		nv_wr32(priv, 0x400824, 0x000000a0);
	}

	switch (nv_device(priv)->chipset) {
	case 0x40:
	case 0x45:
		nv_wr32(priv, 0x4009b8, 0x0078e366);
		nv_wr32(priv, 0x4009bc, 0x0000014c);
		break;
	case 0x41:
	case 0x42: /* pciid also 0x00Cx */
	/* case 0x0120: XXX (pciid) */
		nv_wr32(priv, 0x400828, 0x007596ff);
		nv_wr32(priv, 0x40082c, 0x00000108);
		break;
	case 0x43:
		nv_wr32(priv, 0x400828, 0x0072cb77);
		nv_wr32(priv, 0x40082c, 0x00000108);
		break;
	case 0x44:
	case 0x46: /* G72 */
	case 0x4a:
	case 0x4c: /* G7x-based C51 */
	case 0x4e:
		nv_wr32(priv, 0x400860, 0);
		nv_wr32(priv, 0x400864, 0);
		break;
	case 0x47: /* G70 */
	case 0x49: /* G71 */
	case 0x4b: /* G73 */
		nv_wr32(priv, 0x400828, 0x07830610);
		nv_wr32(priv, 0x40082c, 0x0000016A);
		break;
	default:
		break;
	}

	nv_wr32(priv, 0x400b38, 0x2ffff800);
	nv_wr32(priv, 0x400b3c, 0x00006000);

	/* Tiling related stuff. */
	switch (nv_device(priv)->chipset) {
	case 0x44:
	case 0x4a:
		nv_wr32(priv, 0x400bc4, 0x1003d888);
		nv_wr32(priv, 0x400bbc, 0xb7a7b500);
		break;
	case 0x46:
		nv_wr32(priv, 0x400bc4, 0x0000e024);
		nv_wr32(priv, 0x400bbc, 0xb7a7b520);
		break;
	case 0x4c:
	case 0x4e:
	case 0x67:
		nv_wr32(priv, 0x400bc4, 0x1003d888);
		nv_wr32(priv, 0x400bbc, 0xb7a7b540);
		break;
	default:
		break;
	}

	/* Turn all the tiling regions off. */
	for (i = 0; i < pfb->tile.regions; i++)
		engine->tile_prog(engine, i);

	/* begin RAM config */
	vramsz = pci_resource_len(nv_device(priv)->pdev, 0) - 1;
	switch (nv_device(priv)->chipset) {
	case 0x40:
		nv_wr32(priv, 0x4009A4, nv_rd32(priv, 0x100200));
		nv_wr32(priv, 0x4009A8, nv_rd32(priv, 0x100204));
		nv_wr32(priv, 0x4069A4, nv_rd32(priv, 0x100200));
		nv_wr32(priv, 0x4069A8, nv_rd32(priv, 0x100204));
		nv_wr32(priv, 0x400820, 0);
		nv_wr32(priv, 0x400824, 0);
		nv_wr32(priv, 0x400864, vramsz);
		nv_wr32(priv, 0x400868, vramsz);
		break;
	default:
		switch (nv_device(priv)->chipset) {
		case 0x41:
		case 0x42:
		case 0x43:
		case 0x45:
		case 0x4e:
		case 0x44:
		case 0x4a:
			nv_wr32(priv, 0x4009F0, nv_rd32(priv, 0x100200));
			nv_wr32(priv, 0x4009F4, nv_rd32(priv, 0x100204));
			break;
		default:
			nv_wr32(priv, 0x400DF0, nv_rd32(priv, 0x100200));
			nv_wr32(priv, 0x400DF4, nv_rd32(priv, 0x100204));
			break;
		}
		nv_wr32(priv, 0x4069F0, nv_rd32(priv, 0x100200));
		nv_wr32(priv, 0x4069F4, nv_rd32(priv, 0x100204));
		nv_wr32(priv, 0x400840, 0);
		nv_wr32(priv, 0x400844, 0);
		nv_wr32(priv, 0x4008A0, vramsz);
		nv_wr32(priv, 0x4008A4, vramsz);
		break;
	}

	return 0;
}