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
struct nv04_disp_priv {TYPE_1__ base; } ;
struct nouveau_subdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_event_trigger (int /*<<< orphan*/ ,int) ; 
 int nv_rd32 (struct nv04_disp_priv*,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv04_disp_priv*,int,int) ; 

__attribute__((used)) static void
nv04_disp_intr(struct nouveau_subdev *subdev)
{
	struct nv04_disp_priv *priv = (void *)subdev;
	u32 crtc0 = nv_rd32(priv, 0x600100);
	u32 crtc1 = nv_rd32(priv, 0x602100);

	if (crtc0 & 0x00000001) {
		nouveau_event_trigger(priv->base.vblank, 0);
		nv_wr32(priv, 0x600100, 0x00000001);
	}

	if (crtc1 & 0x00000001) {
		nouveau_event_trigger(priv->base.vblank, 1);
		nv_wr32(priv, 0x602100, 0x00000001);
	}
}