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
struct nv04_devinit_priv {int /*<<< orphan*/  base; int /*<<< orphan*/  owner; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_devinit_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nv_lockvgac (struct nv04_devinit_priv*,int) ; 
 int /*<<< orphan*/  nv_wrvgaowner (struct nv04_devinit_priv*,int /*<<< orphan*/ ) ; 

void
nv04_devinit_dtor(struct nouveau_object *object)
{
	struct nv04_devinit_priv *priv = (void *)object;

	/* restore vga owner saved at first init, and lock crtc regs  */
	nv_wrvgaowner(priv, priv->owner);
	nv_lockvgac(priv, true);

	nouveau_devinit_destroy(&priv->base);
}