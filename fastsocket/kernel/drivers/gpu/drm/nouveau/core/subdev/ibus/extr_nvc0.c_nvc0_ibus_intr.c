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
struct nvc0_ibus_priv {int dummy; } ;
struct nouveau_subdev {int dummy; } ;

/* Variables and functions */
 int nv_rd32 (struct nvc0_ibus_priv*,int) ; 
 int /*<<< orphan*/  nvc0_ibus_intr_gpc (struct nvc0_ibus_priv*,int) ; 
 int /*<<< orphan*/  nvc0_ibus_intr_hub (struct nvc0_ibus_priv*,int) ; 
 int /*<<< orphan*/  nvc0_ibus_intr_rop (struct nvc0_ibus_priv*,int) ; 

__attribute__((used)) static void
nvc0_ibus_intr(struct nouveau_subdev *subdev)
{
	struct nvc0_ibus_priv *priv = (void *)subdev;
	u32 intr0 = nv_rd32(priv, 0x121c58);
	u32 intr1 = nv_rd32(priv, 0x121c5c);
	u32 hubnr = nv_rd32(priv, 0x121c70);
	u32 ropnr = nv_rd32(priv, 0x121c74);
	u32 gpcnr = nv_rd32(priv, 0x121c78);
	u32 i;

	for (i = 0; (intr0 & 0x0000ff00) && i < hubnr; i++) {
		u32 stat = 0x00000100 << i;
		if (intr0 & stat) {
			nvc0_ibus_intr_hub(priv, i);
			intr0 &= ~stat;
		}
	}

	for (i = 0; (intr0 & 0xffff0000) && i < ropnr; i++) {
		u32 stat = 0x00010000 << i;
		if (intr0 & stat) {
			nvc0_ibus_intr_rop(priv, i);
			intr0 &= ~stat;
		}
	}

	for (i = 0; intr1 && i < gpcnr; i++) {
		u32 stat = 0x00000001 << i;
		if (intr1 & stat) {
			nvc0_ibus_intr_gpc(priv, i);
			intr1 &= ~stat;
		}
	}
}