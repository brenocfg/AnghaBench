#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  base; TYPE_1__* fan; } ;
struct nva3_therm_priv {TYPE_2__ base; } ;
struct nouveau_object {int dummy; } ;
struct dcb_gpio_func {scalar_t__ func; int line; } ;
struct TYPE_6__ {int crystal; } ;
struct TYPE_4__ {struct dcb_gpio_func tach; } ;

/* Variables and functions */
 scalar_t__ DCB_GPIO_UNUSED ; 
 int nouveau_therm_init (int /*<<< orphan*/ *) ; 
 TYPE_3__* nv_device (struct nva3_therm_priv*) ; 
 int /*<<< orphan*/  nv_mask (struct nva3_therm_priv*,int,int,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nva3_therm_priv*,int,int) ; 

__attribute__((used)) static int
nva3_therm_init(struct nouveau_object *object)
{
	struct nva3_therm_priv *priv = (void *)object;
	struct dcb_gpio_func *tach = &priv->base.fan->tach;
	int ret;

	ret = nouveau_therm_init(&priv->base.base);
	if (ret)
		return ret;

	/* enable fan tach, count revolutions per-second */
	nv_mask(priv, 0x00e720, 0x00000003, 0x00000002);
	if (tach->func != DCB_GPIO_UNUSED) {
		nv_wr32(priv, 0x00e724, nv_device(priv)->crystal * 1000);
		nv_mask(priv, 0x00e720, 0x001f0000, tach->line << 16);
		nv_mask(priv, 0x00e720, 0x00000001, 0x00000001);
	}
	nv_mask(priv, 0x00e720, 0x00000002, 0x00000000);

	return 0;
}