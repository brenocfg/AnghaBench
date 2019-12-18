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
struct nv04_devinit_priv {scalar_t__ owner; int /*<<< orphan*/  base; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int nouveau_devinit_fini (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nv_lockvgac (struct nv04_devinit_priv*,int) ; 
 int /*<<< orphan*/  nv_mask (struct nv04_devinit_priv*,int,int,int) ; 
 scalar_t__ nv_rdvgaowner (struct nv04_devinit_priv*) ; 
 int /*<<< orphan*/  nv_wrvgaowner (struct nv04_devinit_priv*,int /*<<< orphan*/ ) ; 

int
nv04_devinit_fini(struct nouveau_object *object, bool suspend)
{
	struct nv04_devinit_priv *priv = (void *)object;

	/* make i2c busses accessible */
	nv_mask(priv, 0x000200, 0x00000001, 0x00000001);

	/* unlock extended vga crtc regs, and unslave crtcs */
	nv_lockvgac(priv, false);
	if (priv->owner < 0)
		priv->owner = nv_rdvgaowner(priv);
	nv_wrvgaowner(priv, 0);

	return nouveau_devinit_fini(&priv->base, suspend);
}