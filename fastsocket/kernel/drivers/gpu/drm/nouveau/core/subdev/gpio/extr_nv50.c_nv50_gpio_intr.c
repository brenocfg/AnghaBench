#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  events; } ;
struct nv50_gpio_priv {TYPE_1__ base; } ;
struct nouveau_subdev {int dummy; } ;
struct TYPE_4__ {int chipset; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_event_trigger (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* nv_device (struct nv50_gpio_priv*) ; 
 int nv_rd32 (struct nv50_gpio_priv*,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv50_gpio_priv*,int,int) ; 

void
nv50_gpio_intr(struct nouveau_subdev *subdev)
{
	struct nv50_gpio_priv *priv = (void *)subdev;
	u32 intr0, intr1 = 0;
	u32 hi, lo;
	int i;

	intr0 = nv_rd32(priv, 0xe054) & nv_rd32(priv, 0xe050);
	if (nv_device(priv)->chipset >= 0x90)
		intr1 = nv_rd32(priv, 0xe074) & nv_rd32(priv, 0xe070);

	hi = (intr0 & 0x0000ffff) | (intr1 << 16);
	lo = (intr0 >> 16) | (intr1 & 0xffff0000);

	for (i = 0; (hi | lo) && i < 32; i++) {
		if ((hi | lo) & (1 << i))
			nouveau_event_trigger(priv->base.events, i);
	}

	nv_wr32(priv, 0xe054, intr0);
	if (nv_device(priv)->chipset >= 0x90)
		nv_wr32(priv, 0xe074, intr1);
}