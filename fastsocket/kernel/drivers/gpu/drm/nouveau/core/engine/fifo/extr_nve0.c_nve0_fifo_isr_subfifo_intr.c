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
struct nve0_fifo_priv {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_bitfield_print (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nouveau_client_name_for_fifo_chid (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nv_error (struct nve0_fifo_priv*,char*,int,...) ; 
 int nv_rd32 (struct nve0_fifo_priv*,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nve0_fifo_priv*,int,int) ; 
 int /*<<< orphan*/  nve0_fifo_subfifo_intr ; 
 int /*<<< orphan*/  nve0_fifo_swmthd (struct nve0_fifo_priv*,int,int,int) ; 
 int /*<<< orphan*/  pr_cont (char*) ; 

__attribute__((used)) static void
nve0_fifo_isr_subfifo_intr(struct nve0_fifo_priv *priv, int unit)
{
	u32 stat = nv_rd32(priv, 0x040108 + (unit * 0x2000));
	u32 addr = nv_rd32(priv, 0x0400c0 + (unit * 0x2000));
	u32 data = nv_rd32(priv, 0x0400c4 + (unit * 0x2000));
	u32 chid = nv_rd32(priv, 0x040120 + (unit * 0x2000)) & 0xfff;
	u32 subc = (addr & 0x00070000) >> 16;
	u32 mthd = (addr & 0x00003ffc);
	u32 show = stat;

	if (stat & 0x00200000) {
		if (mthd == 0x0054) {
			if (!nve0_fifo_swmthd(priv, chid, 0x0500, 0x00000000))
				show &= ~0x00200000;
		}
	}

	if (stat & 0x00800000) {
		if (!nve0_fifo_swmthd(priv, chid, mthd, data))
			show &= ~0x00800000;
	}

	if (show) {
		nv_error(priv, "SUBFIFO%d:", unit);
		nouveau_bitfield_print(nve0_fifo_subfifo_intr, show);
		pr_cont("\n");
		nv_error(priv,
			 "SUBFIFO%d: ch %d [%s] subc %d mthd 0x%04x data 0x%08x\n",
			 unit, chid,
			 nouveau_client_name_for_fifo_chid(&priv->base, chid),
			 subc, mthd, data);
	}

	nv_wr32(priv, 0x0400c0 + (unit * 0x2000), 0x80600008);
	nv_wr32(priv, 0x040108 + (unit * 0x2000), stat);
}