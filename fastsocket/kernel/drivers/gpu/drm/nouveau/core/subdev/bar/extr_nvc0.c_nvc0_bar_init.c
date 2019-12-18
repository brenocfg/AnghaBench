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
struct nvc0_bar_priv {TYPE_2__* bar; int /*<<< orphan*/  base; } ;
struct nouveau_object {int dummy; } ;
struct TYPE_4__ {TYPE_1__* mem; } ;
struct TYPE_3__ {int addr; } ;

/* Variables and functions */
 int nouveau_bar_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nv_mask (struct nvc0_bar_priv*,int,int,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nvc0_bar_priv*,int,int) ; 

__attribute__((used)) static int
nvc0_bar_init(struct nouveau_object *object)
{
	struct nvc0_bar_priv *priv = (void *)object;
	int ret;

	ret = nouveau_bar_init(&priv->base);
	if (ret)
		return ret;

	nv_mask(priv, 0x000200, 0x00000100, 0x00000000);
	nv_mask(priv, 0x000200, 0x00000100, 0x00000100);
	nv_mask(priv, 0x100c80, 0x00000001, 0x00000000);

	nv_wr32(priv, 0x001704, 0x80000000 | priv->bar[1].mem->addr >> 12);
	nv_wr32(priv, 0x001714, 0xc0000000 | priv->bar[0].mem->addr >> 12);
	return 0;
}