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
struct nv04_timer_priv {int /*<<< orphan*/  base; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 void nouveau_timer_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nv04_timer_dtor(struct nouveau_object *object)
{
	struct nv04_timer_priv *priv = (void *)object;
	return nouveau_timer_destroy(&priv->base);
}