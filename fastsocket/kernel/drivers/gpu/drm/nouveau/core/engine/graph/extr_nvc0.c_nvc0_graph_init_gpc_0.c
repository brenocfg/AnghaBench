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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct nvc0_graph_priv {int tpc_total; int* tpc_nr; int gpc_nr; int magic_not_rop_nr; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  GPC_BCAST (int) ; 
 int GPC_MAX ; 
 int /*<<< orphan*/  GPC_UNIT (int,int) ; 
 int TPC_MAX ; 
 int /*<<< orphan*/  TPC_UNIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int const nv_rd32 (struct nvc0_graph_priv*,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nvc0_graph_priv*,int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static void
nvc0_graph_init_gpc_0(struct nvc0_graph_priv *priv)
{
	const u32 magicgpc918 = DIV_ROUND_UP(0x00800000, priv->tpc_total);
	u32 data[TPC_MAX / 8];
	u8  tpcnr[GPC_MAX];
	int i, gpc, tpc;

	nv_wr32(priv, TPC_UNIT(0, 0, 0x5c), 1); /* affects TFB offset queries */

	/*
	 *      TP      ROP UNKVAL(magic_not_rop_nr)
	 * 450: 4/0/0/0 2        3
	 * 460: 3/4/0/0 4        1
	 * 465: 3/4/4/0 4        7
	 * 470: 3/3/4/4 5        5
	 * 480: 3/4/4/4 6        6
	 */

	memset(data, 0x00, sizeof(data));
	memcpy(tpcnr, priv->tpc_nr, sizeof(priv->tpc_nr));
	for (i = 0, gpc = -1; i < priv->tpc_total; i++) {
		do {
			gpc = (gpc + 1) % priv->gpc_nr;
		} while (!tpcnr[gpc]);
		tpc = priv->tpc_nr[gpc] - tpcnr[gpc]--;

		data[i / 8] |= tpc << ((i % 8) * 4);
	}

	nv_wr32(priv, GPC_BCAST(0x0980), data[0]);
	nv_wr32(priv, GPC_BCAST(0x0984), data[1]);
	nv_wr32(priv, GPC_BCAST(0x0988), data[2]);
	nv_wr32(priv, GPC_BCAST(0x098c), data[3]);

	for (gpc = 0; gpc < priv->gpc_nr; gpc++) {
		nv_wr32(priv, GPC_UNIT(gpc, 0x0914), priv->magic_not_rop_nr << 8 |
						  priv->tpc_nr[gpc]);
		nv_wr32(priv, GPC_UNIT(gpc, 0x0910), 0x00040000 | priv->tpc_total);
		nv_wr32(priv, GPC_UNIT(gpc, 0x0918), magicgpc918);
	}

	nv_wr32(priv, GPC_BCAST(0x1bd4), magicgpc918);
	nv_wr32(priv, GPC_BCAST(0x08ac), nv_rd32(priv, 0x100800));
}