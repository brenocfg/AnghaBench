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
struct nvc0_graph_priv {int gpc_nr; int rop_nr; } ;

/* Variables and functions */
 int ROP_UNIT (int,int) ; 
 int /*<<< orphan*/  nv_error (struct nvc0_graph_priv*,char*,int,...) ; 
 int nv_rd32 (struct nvc0_graph_priv*,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nvc0_graph_priv*,int,int) ; 
 int /*<<< orphan*/  nvc0_graph_trap_gpc (struct nvc0_graph_priv*,int) ; 

__attribute__((used)) static void
nvc0_graph_trap_intr(struct nvc0_graph_priv *priv)
{
	u32 trap = nv_rd32(priv, 0x400108);
	int rop, gpc;

	if (trap & 0x00000001) {
		u32 stat = nv_rd32(priv, 0x404000);
		nv_error(priv, "DISPATCH 0x%08x\n", stat);
		nv_wr32(priv, 0x404000, 0xc0000000);
		nv_wr32(priv, 0x400108, 0x00000001);
		trap &= ~0x00000001;
	}

	if (trap & 0x00000002) {
		u32 stat = nv_rd32(priv, 0x404600);
		nv_error(priv, "M2MF 0x%08x\n", stat);
		nv_wr32(priv, 0x404600, 0xc0000000);
		nv_wr32(priv, 0x400108, 0x00000002);
		trap &= ~0x00000002;
	}

	if (trap & 0x00000008) {
		u32 stat = nv_rd32(priv, 0x408030);
		nv_error(priv, "CCACHE 0x%08x\n", stat);
		nv_wr32(priv, 0x408030, 0xc0000000);
		nv_wr32(priv, 0x400108, 0x00000008);
		trap &= ~0x00000008;
	}

	if (trap & 0x00000010) {
		u32 stat = nv_rd32(priv, 0x405840);
		nv_error(priv, "SHADER 0x%08x\n", stat);
		nv_wr32(priv, 0x405840, 0xc0000000);
		nv_wr32(priv, 0x400108, 0x00000010);
		trap &= ~0x00000010;
	}

	if (trap & 0x00000040) {
		u32 stat = nv_rd32(priv, 0x40601c);
		nv_error(priv, "UNK6 0x%08x\n", stat);
		nv_wr32(priv, 0x40601c, 0xc0000000);
		nv_wr32(priv, 0x400108, 0x00000040);
		trap &= ~0x00000040;
	}

	if (trap & 0x00000080) {
		u32 stat = nv_rd32(priv, 0x404490);
		nv_error(priv, "MACRO 0x%08x\n", stat);
		nv_wr32(priv, 0x404490, 0xc0000000);
		nv_wr32(priv, 0x400108, 0x00000080);
		trap &= ~0x00000080;
	}

	if (trap & 0x01000000) {
		u32 stat = nv_rd32(priv, 0x400118);
		for (gpc = 0; stat && gpc < priv->gpc_nr; gpc++) {
			u32 mask = 0x00000001 << gpc;
			if (stat & mask) {
				nvc0_graph_trap_gpc(priv, gpc);
				nv_wr32(priv, 0x400118, mask);
				stat &= ~mask;
			}
		}
		nv_wr32(priv, 0x400108, 0x01000000);
		trap &= ~0x01000000;
	}

	if (trap & 0x02000000) {
		for (rop = 0; rop < priv->rop_nr; rop++) {
			u32 statz = nv_rd32(priv, ROP_UNIT(rop, 0x070));
			u32 statc = nv_rd32(priv, ROP_UNIT(rop, 0x144));
			nv_error(priv, "ROP%d 0x%08x 0x%08x\n",
				 rop, statz, statc);
			nv_wr32(priv, ROP_UNIT(rop, 0x070), 0xc0000000);
			nv_wr32(priv, ROP_UNIT(rop, 0x144), 0xc0000000);
		}
		nv_wr32(priv, 0x400108, 0x02000000);
		trap &= ~0x02000000;
	}

	if (trap) {
		nv_error(priv, "TRAP UNHANDLED 0x%08x\n", trap);
		nv_wr32(priv, 0x400108, trap);
	}
}