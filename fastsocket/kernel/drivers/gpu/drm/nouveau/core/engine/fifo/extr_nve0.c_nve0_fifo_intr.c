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
struct TYPE_2__ {int /*<<< orphan*/  uevent; } ;
struct nve0_fifo_priv {TYPE_1__ base; } ;
struct nouveau_subdev {int dummy; } ;

/* Variables and functions */
 int ffs (int) ; 
 int /*<<< orphan*/  nouveau_event_trigger (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_fatal (struct nve0_fifo_priv*,char*,int) ; 
 int /*<<< orphan*/  nv_mask (struct nve0_fifo_priv*,int,int,int) ; 
 int nv_rd32 (struct nve0_fifo_priv*,int) ; 
 int /*<<< orphan*/  nv_warn (struct nve0_fifo_priv*,char*) ; 
 int /*<<< orphan*/  nv_wr32 (struct nve0_fifo_priv*,int,int) ; 
 int /*<<< orphan*/  nve0_fifo_isr_subfifo_intr (struct nve0_fifo_priv*,int) ; 
 int /*<<< orphan*/  nve0_fifo_isr_vm_fault (struct nve0_fifo_priv*,int) ; 

__attribute__((used)) static void
nve0_fifo_intr(struct nouveau_subdev *subdev)
{
	struct nve0_fifo_priv *priv = (void *)subdev;
	u32 mask = nv_rd32(priv, 0x002140);
	u32 stat = nv_rd32(priv, 0x002100) & mask;

	if (stat & 0x00000100) {
		nv_warn(priv, "unknown status 0x00000100\n");
		nv_wr32(priv, 0x002100, 0x00000100);
		stat &= ~0x00000100;
	}

	if (stat & 0x10000000) {
		u32 units = nv_rd32(priv, 0x00259c);
		u32 u = units;

		while (u) {
			int i = ffs(u) - 1;
			nve0_fifo_isr_vm_fault(priv, i);
			u &= ~(1 << i);
		}

		nv_wr32(priv, 0x00259c, units);
		stat &= ~0x10000000;
	}

	if (stat & 0x20000000) {
		u32 units = nv_rd32(priv, 0x0025a0);
		u32 u = units;

		while (u) {
			int i = ffs(u) - 1;
			nve0_fifo_isr_subfifo_intr(priv, i);
			u &= ~(1 << i);
		}

		nv_wr32(priv, 0x0025a0, units);
		stat &= ~0x20000000;
	}

	if (stat & 0x40000000) {
		nv_warn(priv, "unknown status 0x40000000\n");
		nv_mask(priv, 0x002a00, 0x00000000, 0x00000000);
		stat &= ~0x40000000;
	}

	if (stat & 0x80000000) {
		nouveau_event_trigger(priv->base.uevent, 0);
		nv_wr32(priv, 0x002100, 0x80000000);
		stat &= ~0x80000000;
	}

	if (stat) {
		nv_fatal(priv, "unhandled status 0x%08x\n", stat);
		nv_wr32(priv, 0x002100, stat);
		nv_wr32(priv, 0x002140, 0);
	}
}