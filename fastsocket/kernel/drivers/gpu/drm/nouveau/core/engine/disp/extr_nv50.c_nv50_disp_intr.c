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
struct TYPE_2__ {int /*<<< orphan*/  vblank; } ;
struct nv50_disp_priv {int super; int /*<<< orphan*/  supervisor; TYPE_1__ base; } ;
struct nouveau_subdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_event_trigger (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nv50_disp_intr_error (struct nv50_disp_priv*) ; 
 int nv_rd32 (struct nv50_disp_priv*,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv50_disp_priv*,int,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

void
nv50_disp_intr(struct nouveau_subdev *subdev)
{
	struct nv50_disp_priv *priv = (void *)subdev;
	u32 intr0 = nv_rd32(priv, 0x610020);
	u32 intr1 = nv_rd32(priv, 0x610024);

	if (intr0 & 0x001f0000) {
		nv50_disp_intr_error(priv);
		intr0 &= ~0x001f0000;
	}

	if (intr1 & 0x00000004) {
		nouveau_event_trigger(priv->base.vblank, 0);
		nv_wr32(priv, 0x610024, 0x00000004);
		intr1 &= ~0x00000004;
	}

	if (intr1 & 0x00000008) {
		nouveau_event_trigger(priv->base.vblank, 1);
		nv_wr32(priv, 0x610024, 0x00000008);
		intr1 &= ~0x00000008;
	}

	if (intr1 & 0x00000070) {
		priv->super = (intr1 & 0x00000070);
		schedule_work(&priv->supervisor);
		nv_wr32(priv, 0x610024, priv->super);
		intr1 &= ~0x00000070;
	}
}