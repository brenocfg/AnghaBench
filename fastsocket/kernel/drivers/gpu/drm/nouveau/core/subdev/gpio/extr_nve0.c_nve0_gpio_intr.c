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
struct TYPE_2__ {int /*<<< orphan*/  events; } ;
struct nve0_gpio_priv {TYPE_1__ base; } ;
struct nouveau_subdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_event_trigger (int /*<<< orphan*/ ,int) ; 
 int nv_rd32 (struct nve0_gpio_priv*,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nve0_gpio_priv*,int,int) ; 

void
nve0_gpio_intr(struct nouveau_subdev *subdev)
{
	struct nve0_gpio_priv *priv = (void *)subdev;
	u32 intr0 = nv_rd32(priv, 0xdc00) & nv_rd32(priv, 0xdc08);
	u32 intr1 = nv_rd32(priv, 0xdc80) & nv_rd32(priv, 0xdc88);
	u32 hi = (intr0 & 0x0000ffff) | (intr1 << 16);
	u32 lo = (intr0 >> 16) | (intr1 & 0xffff0000);
	int i;

	for (i = 0; (hi | lo) && i < 32; i++) {
		if ((hi | lo) & (1 << i))
			nouveau_event_trigger(priv->base.events, i);
	}

	nv_wr32(priv, 0xdc00, intr0);
	nv_wr32(priv, 0xdc88, intr1);
}