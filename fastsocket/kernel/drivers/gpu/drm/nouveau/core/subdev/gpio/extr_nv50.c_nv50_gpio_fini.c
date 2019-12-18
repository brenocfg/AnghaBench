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
struct nv50_gpio_priv {int /*<<< orphan*/  base; } ;
struct nouveau_object {int dummy; } ;
struct TYPE_2__ {int chipset; } ;

/* Variables and functions */
 int nouveau_gpio_fini (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* nv_device (struct nv50_gpio_priv*) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv50_gpio_priv*,int,int) ; 

int
nv50_gpio_fini(struct nouveau_object *object, bool suspend)
{
	struct nv50_gpio_priv *priv = (void *)object;
	nv_wr32(priv, 0xe050, 0x00000000);
	if (nv_device(priv)->chipset >= 0x90)
		nv_wr32(priv, 0xe070, 0x00000000);
	return nouveau_gpio_fini(&priv->base, suspend);
}