#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nv50_graph_priv {int dummy; } ;
struct TYPE_2__ {int chipset; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv50_priv_mp_trap (struct nv50_graph_priv*,int,int) ; 
 TYPE_1__* nv_device (struct nv50_graph_priv*) ; 
 int /*<<< orphan*/  nv_error (struct nv50_graph_priv*,char*,...) ; 
 int nv_rd32 (struct nv50_graph_priv*,int) ; 
 int /*<<< orphan*/  nv_warn (struct nv50_graph_priv*,char*,char const*) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv50_graph_priv*,int,int) ; 

__attribute__((used)) static void
nv50_priv_tp_trap(struct nv50_graph_priv *priv, int type, u32 ustatus_old,
		u32 ustatus_new, int display, const char *name)
{
	int tps = 0;
	u32 units = nv_rd32(priv, 0x1540);
	int i, r;
	u32 ustatus_addr, ustatus;
	for (i = 0; i < 16; i++) {
		if (!(units & (1 << i)))
			continue;
		if (nv_device(priv)->chipset < 0xa0)
			ustatus_addr = ustatus_old + (i << 12);
		else
			ustatus_addr = ustatus_new + (i << 11);
		ustatus = nv_rd32(priv, ustatus_addr) & 0x7fffffff;
		if (!ustatus)
			continue;
		tps++;
		switch (type) {
		case 6: /* texture error... unknown for now */
			if (display) {
				nv_error(priv, "magic set %d:\n", i);
				for (r = ustatus_addr + 4; r <= ustatus_addr + 0x10; r += 4)
					nv_error(priv, "\t0x%08x: 0x%08x\n", r,
						nv_rd32(priv, r));
			}
			break;
		case 7: /* MP error */
			if (ustatus & 0x04030000) {
				nv50_priv_mp_trap(priv, i, display);
				ustatus &= ~0x04030000;
			}
			break;
		case 8: /* TPDMA error */
			{
			u32 e0c = nv_rd32(priv, ustatus_addr + 4);
			u32 e10 = nv_rd32(priv, ustatus_addr + 8);
			u32 e14 = nv_rd32(priv, ustatus_addr + 0xc);
			u32 e18 = nv_rd32(priv, ustatus_addr + 0x10);
			u32 e1c = nv_rd32(priv, ustatus_addr + 0x14);
			u32 e20 = nv_rd32(priv, ustatus_addr + 0x18);
			u32 e24 = nv_rd32(priv, ustatus_addr + 0x1c);
			/* 2d engine destination */
			if (ustatus & 0x00000010) {
				if (display) {
					nv_error(priv, "TRAP_TPDMA_2D - TP %d - Unknown fault at address %02x%08x\n",
							i, e14, e10);
					nv_error(priv, "TRAP_TPDMA_2D - TP %d - e0c: %08x, e18: %08x, e1c: %08x, e20: %08x, e24: %08x\n",
							i, e0c, e18, e1c, e20, e24);
				}
				ustatus &= ~0x00000010;
			}
			/* Render target */
			if (ustatus & 0x00000040) {
				if (display) {
					nv_error(priv, "TRAP_TPDMA_RT - TP %d - Unknown fault at address %02x%08x\n",
							i, e14, e10);
					nv_error(priv, "TRAP_TPDMA_RT - TP %d - e0c: %08x, e18: %08x, e1c: %08x, e20: %08x, e24: %08x\n",
							i, e0c, e18, e1c, e20, e24);
				}
				ustatus &= ~0x00000040;
			}
			/* CUDA memory: l[], g[] or stack. */
			if (ustatus & 0x00000080) {
				if (display) {
					if (e18 & 0x80000000) {
						/* g[] read fault? */
						nv_error(priv, "TRAP_TPDMA - TP %d - Global read fault at address %02x%08x\n",
								i, e14, e10 | ((e18 >> 24) & 0x1f));
						e18 &= ~0x1f000000;
					} else if (e18 & 0xc) {
						/* g[] write fault? */
						nv_error(priv, "TRAP_TPDMA - TP %d - Global write fault at address %02x%08x\n",
								i, e14, e10 | ((e18 >> 7) & 0x1f));
						e18 &= ~0x00000f80;
					} else {
						nv_error(priv, "TRAP_TPDMA - TP %d - Unknown CUDA fault at address %02x%08x\n",
								i, e14, e10);
					}
					nv_error(priv, "TRAP_TPDMA - TP %d - e0c: %08x, e18: %08x, e1c: %08x, e20: %08x, e24: %08x\n",
							i, e0c, e18, e1c, e20, e24);
				}
				ustatus &= ~0x00000080;
			}
			}
			break;
		}
		if (ustatus) {
			if (display)
				nv_error(priv, "%s - TP%d: Unhandled ustatus 0x%08x\n", name, i, ustatus);
		}
		nv_wr32(priv, ustatus_addr, 0xc0000000);
	}

	if (!tps && display)
		nv_warn(priv, "%s - No TPs claiming errors?\n", name);
}