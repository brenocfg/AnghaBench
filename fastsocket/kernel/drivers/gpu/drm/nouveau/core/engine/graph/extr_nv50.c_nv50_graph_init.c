#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nv50_graph_priv {int /*<<< orphan*/  size; int /*<<< orphan*/  base; } ;
struct nouveau_object {int dummy; } ;
struct TYPE_3__ {int chipset; } ;

/* Variables and functions */
 int nouveau_graph_init (int /*<<< orphan*/ *) ; 
 int nv50_grctx_init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* nv_device (struct nv50_graph_priv*) ; 
 int nv_rd32 (struct nv50_graph_priv*,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv50_graph_priv*,int,int) ; 

__attribute__((used)) static int
nv50_graph_init(struct nouveau_object *object)
{
	struct nv50_graph_priv *priv = (void *)object;
	int ret, units, i;

	ret = nouveau_graph_init(&priv->base);
	if (ret)
		return ret;

	/* NV_PGRAPH_DEBUG_3_HW_CTX_SWITCH_ENABLED */
	nv_wr32(priv, 0x40008c, 0x00000004);

	/* reset/enable traps and interrupts */
	nv_wr32(priv, 0x400804, 0xc0000000);
	nv_wr32(priv, 0x406800, 0xc0000000);
	nv_wr32(priv, 0x400c04, 0xc0000000);
	nv_wr32(priv, 0x401800, 0xc0000000);
	nv_wr32(priv, 0x405018, 0xc0000000);
	nv_wr32(priv, 0x402000, 0xc0000000);

	units = nv_rd32(priv, 0x001540);
	for (i = 0; i < 16; i++) {
		if (!(units & (1 << i)))
			continue;

		if (nv_device(priv)->chipset < 0xa0) {
			nv_wr32(priv, 0x408900 + (i << 12), 0xc0000000);
			nv_wr32(priv, 0x408e08 + (i << 12), 0xc0000000);
			nv_wr32(priv, 0x408314 + (i << 12), 0xc0000000);
		} else {
			nv_wr32(priv, 0x408600 + (i << 11), 0xc0000000);
			nv_wr32(priv, 0x408708 + (i << 11), 0xc0000000);
			nv_wr32(priv, 0x40831c + (i << 11), 0xc0000000);
		}
	}

	nv_wr32(priv, 0x400108, 0xffffffff);
	nv_wr32(priv, 0x400138, 0xffffffff);
	nv_wr32(priv, 0x400100, 0xffffffff);
	nv_wr32(priv, 0x40013c, 0xffffffff);
	nv_wr32(priv, 0x400500, 0x00010001);

	/* upload context program, initialise ctxctl defaults */
	ret = nv50_grctx_init(nv_device(priv), &priv->size);
	if (ret)
		return ret;

	nv_wr32(priv, 0x400824, 0x00000000);
	nv_wr32(priv, 0x400828, 0x00000000);
	nv_wr32(priv, 0x40082c, 0x00000000);
	nv_wr32(priv, 0x400830, 0x00000000);
	nv_wr32(priv, 0x40032c, 0x00000000);
	nv_wr32(priv, 0x400330, 0x00000000);

	/* some unknown zcull magic */
	switch (nv_device(priv)->chipset & 0xf0) {
	case 0x50:
	case 0x80:
	case 0x90:
		nv_wr32(priv, 0x402ca8, 0x00000800);
		break;
	case 0xa0:
	default:
		nv_wr32(priv, 0x402cc0, 0x00000000);
		if (nv_device(priv)->chipset == 0xa0 ||
		    nv_device(priv)->chipset == 0xaa ||
		    nv_device(priv)->chipset == 0xac) {
			nv_wr32(priv, 0x402ca8, 0x00000802);
		} else {
			nv_wr32(priv, 0x402cc0, 0x00000000);
			nv_wr32(priv, 0x402ca8, 0x00000002);
		}

		break;
	}

	/* zero out zcull regions */
	for (i = 0; i < 8; i++) {
		nv_wr32(priv, 0x402c20 + (i * 8), 0x00000000);
		nv_wr32(priv, 0x402c24 + (i * 8), 0x00000000);
		nv_wr32(priv, 0x402c28 + (i * 8), 0x00000000);
		nv_wr32(priv, 0x402c2c + (i * 8), 0x00000000);
	}
	return 0;
}