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
struct nv50_devinit_priv {int /*<<< orphan*/  base; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_devinit_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nv50_devinit_dtor(struct nouveau_object *object)
{
	struct nv50_devinit_priv *priv = (void *)object;
	nouveau_devinit_destroy(&priv->base);
}