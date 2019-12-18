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
struct nv10_gpio_priv {int /*<<< orphan*/  base; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int nouveau_gpio_fini (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv10_gpio_priv*,int,int) ; 

__attribute__((used)) static int
nv10_gpio_fini(struct nouveau_object *object, bool suspend)
{
	struct nv10_gpio_priv *priv = (void *)object;
	nv_wr32(priv, 0x001144, 0x00000000);
	return nouveau_gpio_fini(&priv->base, suspend);
}