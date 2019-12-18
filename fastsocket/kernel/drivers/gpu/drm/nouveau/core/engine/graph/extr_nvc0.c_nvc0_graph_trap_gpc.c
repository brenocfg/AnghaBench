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
struct nvc0_graph_priv {int* tpc_nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPC_UNIT (int,int) ; 
 int /*<<< orphan*/  nv_error (struct nvc0_graph_priv*,char*,int,int) ; 
 int nv_rd32 (struct nvc0_graph_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_wr32 (struct nvc0_graph_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvc0_graph_trap_tpc (struct nvc0_graph_priv*,int,int) ; 

__attribute__((used)) static void
nvc0_graph_trap_gpc(struct nvc0_graph_priv *priv, int gpc)
{
	u32 stat = nv_rd32(priv, GPC_UNIT(gpc, 0x2c90));
	int tpc;

	if (stat & 0x00000001) {
		u32 trap = nv_rd32(priv, GPC_UNIT(gpc, 0x0420));
		nv_error(priv, "GPC%d/PROP: 0x%08x\n", gpc, trap);
		nv_wr32(priv, GPC_UNIT(gpc, 0x0420), 0xc0000000);
		nv_wr32(priv, GPC_UNIT(gpc, 0x2c90), 0x00000001);
		stat &= ~0x00000001;
	}

	if (stat & 0x00000002) {
		u32 trap = nv_rd32(priv, GPC_UNIT(gpc, 0x0900));
		nv_error(priv, "GPC%d/ZCULL: 0x%08x\n", gpc, trap);
		nv_wr32(priv, GPC_UNIT(gpc, 0x0900), 0xc0000000);
		nv_wr32(priv, GPC_UNIT(gpc, 0x2c90), 0x00000002);
		stat &= ~0x00000002;
	}

	if (stat & 0x00000004) {
		u32 trap = nv_rd32(priv, GPC_UNIT(gpc, 0x1028));
		nv_error(priv, "GPC%d/CCACHE: 0x%08x\n", gpc, trap);
		nv_wr32(priv, GPC_UNIT(gpc, 0x1028), 0xc0000000);
		nv_wr32(priv, GPC_UNIT(gpc, 0x2c90), 0x00000004);
		stat &= ~0x00000004;
	}

	if (stat & 0x00000008) {
		u32 trap = nv_rd32(priv, GPC_UNIT(gpc, 0x0824));
		nv_error(priv, "GPC%d/ESETUP: 0x%08x\n", gpc, trap);
		nv_wr32(priv, GPC_UNIT(gpc, 0x0824), 0xc0000000);
		nv_wr32(priv, GPC_UNIT(gpc, 0x2c90), 0x00000008);
		stat &= ~0x00000009;
	}

	for (tpc = 0; tpc < priv->tpc_nr[gpc]; tpc++) {
		u32 mask = 0x00010000 << tpc;
		if (stat & mask) {
			nvc0_graph_trap_tpc(priv, gpc, tpc);
			nv_wr32(priv, GPC_UNIT(gpc, 0x2c90), mask);
			stat &= ~mask;
		}
	}

	if (stat) {
		nv_error(priv, "GPC%d/0x%08x: unknown\n", gpc, stat);
		nv_wr32(priv, GPC_UNIT(gpc, 0x2c90), stat);
	}
}