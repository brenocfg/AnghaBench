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
 int /*<<< orphan*/  nouveau_enum_print (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nv50_mp_exec_error_names ; 
 TYPE_1__* nv_device (struct nv50_graph_priv*) ; 
 int /*<<< orphan*/  nv_error (struct nv50_graph_priv*,char*,int,...) ; 
 int nv_rd32 (struct nv50_graph_priv*,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv50_graph_priv*,int,int) ; 
 int /*<<< orphan*/  pr_cont (char*,int,int,int,int) ; 

__attribute__((used)) static void
nv50_priv_mp_trap(struct nv50_graph_priv *priv, int tpid, int display)
{
	u32 units = nv_rd32(priv, 0x1540);
	u32 addr, mp10, status, pc, oplow, ophigh;
	int i;
	int mps = 0;
	for (i = 0; i < 4; i++) {
		if (!(units & 1 << (i+24)))
			continue;
		if (nv_device(priv)->chipset < 0xa0)
			addr = 0x408200 + (tpid << 12) + (i << 7);
		else
			addr = 0x408100 + (tpid << 11) + (i << 7);
		mp10 = nv_rd32(priv, addr + 0x10);
		status = nv_rd32(priv, addr + 0x14);
		if (!status)
			continue;
		if (display) {
			nv_rd32(priv, addr + 0x20);
			pc = nv_rd32(priv, addr + 0x24);
			oplow = nv_rd32(priv, addr + 0x70);
			ophigh = nv_rd32(priv, addr + 0x74);
			nv_error(priv, "TRAP_MP_EXEC - "
					"TP %d MP %d: ", tpid, i);
			nouveau_enum_print(nv50_mp_exec_error_names, status);
			pr_cont(" at %06x warp %d, opcode %08x %08x\n",
					pc&0xffffff, pc >> 24,
					oplow, ophigh);
		}
		nv_wr32(priv, addr + 0x10, mp10);
		nv_wr32(priv, addr + 0x14, 0);
		mps++;
	}
	if (!mps && display)
		nv_error(priv, "TRAP_MP_EXEC - TP %d: "
				"No MPs claiming errors?\n", tpid);
}