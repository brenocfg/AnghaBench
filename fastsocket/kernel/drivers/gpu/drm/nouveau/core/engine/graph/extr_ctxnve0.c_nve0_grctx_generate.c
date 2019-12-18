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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct nvc0_grctx {int dummy; } ;
struct nvc0_graph_priv {int gpc_nr; int* tpc_nr; int tpc_total; int magic_not_rop_nr; } ;

/* Variables and functions */
 int GPC_MAX ; 
 int GPC_UNIT (int,int) ; 
 int NV_MEM_ACCESS_RW ; 
 int NV_MEM_ACCESS_SYS ; 
 int TPC_UNIT (int,int,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  mmio_data (int,int,int) ; 
 int /*<<< orphan*/  mmio_list (int,int,int,int) ; 
 int /*<<< orphan*/  nv_mask (struct nvc0_graph_priv*,int,int,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nvc0_graph_priv*,int,int) ; 
 int nvc0_grctx_fini (struct nvc0_grctx*) ; 
 int nvc0_grctx_init (struct nvc0_graph_priv*,struct nvc0_grctx*) ; 
 int /*<<< orphan*/  nve0_graph_generate_gpc (struct nvc0_graph_priv*) ; 
 int /*<<< orphan*/  nve0_graph_generate_tpc (struct nvc0_graph_priv*) ; 
 int /*<<< orphan*/  nve0_graph_generate_tpcunk (struct nvc0_graph_priv*) ; 
 int /*<<< orphan*/  nve0_graph_generate_unk40xx (struct nvc0_graph_priv*) ; 
 int /*<<< orphan*/  nve0_graph_generate_unk44xx (struct nvc0_graph_priv*) ; 
 int /*<<< orphan*/  nve0_graph_generate_unk46xx (struct nvc0_graph_priv*) ; 
 int /*<<< orphan*/  nve0_graph_generate_unk47xx (struct nvc0_graph_priv*) ; 
 int /*<<< orphan*/  nve0_graph_generate_unk58xx (struct nvc0_graph_priv*) ; 
 int /*<<< orphan*/  nve0_graph_generate_unk60xx (struct nvc0_graph_priv*) ; 
 int /*<<< orphan*/  nve0_graph_generate_unk64xx (struct nvc0_graph_priv*) ; 
 int /*<<< orphan*/  nve0_graph_generate_unk70xx (struct nvc0_graph_priv*) ; 
 int /*<<< orphan*/  nve0_graph_generate_unk78xx (struct nvc0_graph_priv*) ; 
 int /*<<< orphan*/  nve0_graph_generate_unk80xx (struct nvc0_graph_priv*) ; 
 int /*<<< orphan*/  nve0_graph_generate_unk88xx (struct nvc0_graph_priv*) ; 
 int /*<<< orphan*/  nve0_grctx_generate_902d (struct nvc0_graph_priv*) ; 
 int /*<<< orphan*/  nve0_grctx_generate_a097 (struct nvc0_graph_priv*) ; 
 int /*<<< orphan*/  nve0_grctx_generate_icmd (struct nvc0_graph_priv*) ; 

int
nve0_grctx_generate(struct nvc0_graph_priv *priv)
{
	struct nvc0_grctx info;
	int ret, i, gpc, tpc, id;
	u32 data[6] = {}, data2[2] = {}, tmp;
	u32 tpc_set = 0, tpc_mask = 0;
	u32 magic[GPC_MAX][2], offset;
	u8 tpcnr[GPC_MAX], a, b;
	u8 shift, ntpcv;

	ret = nvc0_grctx_init(priv, &info);
	if (ret)
		return ret;

	nv_mask(priv, 0x000260, 0x00000001, 0x00000000);
	nv_wr32(priv, 0x400204, 0x00000000);
	nv_wr32(priv, 0x400208, 0x00000000);

	nve0_graph_generate_unk40xx(priv);
	nve0_graph_generate_unk44xx(priv);
	nve0_graph_generate_unk46xx(priv);
	nve0_graph_generate_unk47xx(priv);
	nve0_graph_generate_unk58xx(priv);
	nve0_graph_generate_unk60xx(priv);
	nve0_graph_generate_unk64xx(priv);
	nve0_graph_generate_unk70xx(priv);
	nve0_graph_generate_unk78xx(priv);
	nve0_graph_generate_unk80xx(priv);
	nve0_graph_generate_unk88xx(priv);
	nve0_graph_generate_gpc(priv);
	nve0_graph_generate_tpc(priv);
	nve0_graph_generate_tpcunk(priv);

	nv_wr32(priv, 0x404154, 0x0);

	mmio_data(0x003000, 0x0100, NV_MEM_ACCESS_RW | NV_MEM_ACCESS_SYS);
	mmio_data(0x008000, 0x0100, NV_MEM_ACCESS_RW | NV_MEM_ACCESS_SYS);
	mmio_data(0x060000, 0x1000, NV_MEM_ACCESS_RW);
	mmio_list(0x40800c, 0x00000000,  8, 1);
	mmio_list(0x408010, 0x80000000,  0, 0);
	mmio_list(0x419004, 0x00000000,  8, 1);
	mmio_list(0x419008, 0x00000000,  0, 0);
	mmio_list(0x4064cc, 0x80000000,  0, 0);
	mmio_list(0x408004, 0x00000000,  8, 0);
	mmio_list(0x408008, 0x80000030,  0, 0);
	mmio_list(0x418808, 0x00000000,  8, 0);
	mmio_list(0x41880c, 0x80000030,  0, 0);
	mmio_list(0x4064c8, 0x01800600,  0, 0);
	mmio_list(0x418810, 0x80000000, 12, 2);
	mmio_list(0x419848, 0x10000000, 12, 2);
	mmio_list(0x405830, 0x02180648,  0, 0);
	mmio_list(0x4064c4, 0x0192ffff,  0, 0);
	for (gpc = 0, offset = 0; gpc < priv->gpc_nr; gpc++) {
		u16 magic0 = 0x0218 * priv->tpc_nr[gpc];
		u16 magic1 = 0x0648 * priv->tpc_nr[gpc];
		magic[gpc][0]  = 0x10000000 | (magic0 << 16) | offset;
		magic[gpc][1]  = 0x00000000 | (magic1 << 16);
		offset += 0x0324 * priv->tpc_nr[gpc];
	}
	for (gpc = 0; gpc < priv->gpc_nr; gpc++) {
		mmio_list(GPC_UNIT(gpc, 0x30c0), magic[gpc][0], 0, 0);
		mmio_list(GPC_UNIT(gpc, 0x30e4), magic[gpc][1] | offset, 0, 0);
		offset += 0x07ff * priv->tpc_nr[gpc];
	}
	mmio_list(0x17e91c, 0x06060609, 0, 0);
	mmio_list(0x17e920, 0x00090a05, 0, 0);

	nv_wr32(priv, 0x418c6c, 0x1);
	nv_wr32(priv, 0x41980c, 0x10);
	nv_wr32(priv, 0x41be08, 0x4);
	nv_wr32(priv, 0x4064c0, 0x801a00f0);
	nv_wr32(priv, 0x405800, 0xf8000bf);
	nv_wr32(priv, 0x419c00, 0xa);

	for (tpc = 0, id = 0; tpc < 4; tpc++) {
		for (gpc = 0; gpc < priv->gpc_nr; gpc++) {
			if (tpc < priv->tpc_nr[gpc]) {
				nv_wr32(priv, TPC_UNIT(gpc, tpc, 0x0698), id);
				nv_wr32(priv, TPC_UNIT(gpc, tpc, 0x04e8), id);
				nv_wr32(priv, GPC_UNIT(gpc, 0x0c10 + tpc * 4), id);
				nv_wr32(priv, TPC_UNIT(gpc, tpc, 0x0088), id++);
			}

			nv_wr32(priv, GPC_UNIT(gpc, 0x0c08), priv->tpc_nr[gpc]);
			nv_wr32(priv, GPC_UNIT(gpc, 0x0c8c), priv->tpc_nr[gpc]);
		}
	}

	tmp = 0;
	for (i = 0; i < priv->gpc_nr; i++)
		tmp |= priv->tpc_nr[i] << (i * 4);
	nv_wr32(priv, 0x406028, tmp);
	nv_wr32(priv, 0x405870, tmp);

	nv_wr32(priv, 0x40602c, 0x0);
	nv_wr32(priv, 0x405874, 0x0);
	nv_wr32(priv, 0x406030, 0x0);
	nv_wr32(priv, 0x405878, 0x0);
	nv_wr32(priv, 0x406034, 0x0);
	nv_wr32(priv, 0x40587c, 0x0);

	/* calculate first set of magics */
	memcpy(tpcnr, priv->tpc_nr, sizeof(priv->tpc_nr));

	gpc = -1;
	for (tpc = 0; tpc < priv->tpc_total; tpc++) {
		do {
			gpc = (gpc + 1) % priv->gpc_nr;
		} while (!tpcnr[gpc]);
		tpcnr[gpc]--;

		data[tpc / 6] |= gpc << ((tpc % 6) * 5);
	}

	for (; tpc < 32; tpc++)
		data[tpc / 6] |= 7 << ((tpc % 6) * 5);

	/* and the second... */
	shift = 0;
	ntpcv = priv->tpc_total;
	while (!(ntpcv & (1 << 4))) {
		ntpcv <<= 1;
		shift++;
	}

	data2[0]  = ntpcv << 16;
	data2[0] |= shift << 21;
	data2[0] |= (((1 << (0 + 5)) % ntpcv) << 24);
	data2[0] |= priv->tpc_total << 8;
	data2[0] |= priv->magic_not_rop_nr;
	for (i = 1; i < 7; i++)
		data2[1] |= ((1 << (i + 5)) % ntpcv) << ((i - 1) * 5);

	/* and write it all the various parts of PGRAPH */
	nv_wr32(priv, 0x418bb8, (priv->tpc_total << 8) | priv->magic_not_rop_nr);
	for (i = 0; i < 6; i++)
		nv_wr32(priv, 0x418b08 + (i * 4), data[i]);

	nv_wr32(priv, 0x41bfd0, data2[0]);
	nv_wr32(priv, 0x41bfe4, data2[1]);
	for (i = 0; i < 6; i++)
		nv_wr32(priv, 0x41bf00 + (i * 4), data[i]);

	nv_wr32(priv, 0x4078bc, (priv->tpc_total << 8) | priv->magic_not_rop_nr);
	for (i = 0; i < 6; i++)
		nv_wr32(priv, 0x40780c + (i * 4), data[i]);


	memcpy(tpcnr, priv->tpc_nr, sizeof(priv->tpc_nr));
	for (gpc = 0; gpc < priv->gpc_nr; gpc++)
		tpc_mask |= ((1 << priv->tpc_nr[gpc]) - 1) << (gpc * 8);

	for (i = 0, gpc = -1, b = -1; i < 32; i++) {
		a = (i * (priv->tpc_total - 1)) / 32;
		if (a != b) {
			b = a;
			do {
				gpc = (gpc + 1) % priv->gpc_nr;
			} while (!tpcnr[gpc]);
			tpc = priv->tpc_nr[gpc] - tpcnr[gpc]--;

			tpc_set |= 1 << ((gpc * 8) + tpc);
		}

		nv_wr32(priv, 0x406800 + (i * 0x20), tpc_set);
		nv_wr32(priv, 0x406c00 + (i * 0x20), tpc_set ^ tpc_mask);
	}

	for (i = 0; i < 8; i++)
		nv_wr32(priv, 0x4064d0 + (i * 0x04), 0x00000000);

	nv_wr32(priv, 0x405b00, 0x201);
	nv_wr32(priv, 0x408850, 0x2);
	nv_wr32(priv, 0x408958, 0x2);
	nv_wr32(priv, 0x419f78, 0xa);

	nve0_grctx_generate_icmd(priv);
	nve0_grctx_generate_a097(priv);
	nve0_grctx_generate_902d(priv);

	nv_mask(priv, 0x000260, 0x00000001, 0x00000001);
	nv_wr32(priv, 0x418800, 0x7026860a); //XXX
	nv_wr32(priv, 0x41be10, 0x00bb8bc7); //XXX
	return nvc0_grctx_fini(&info);
}