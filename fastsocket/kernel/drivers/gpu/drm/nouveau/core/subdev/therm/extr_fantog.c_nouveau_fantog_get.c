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
struct nouveau_therm_priv {scalar_t__ fan; } ;
struct nouveau_therm {int dummy; } ;
struct nouveau_fantog_priv {int percent; } ;

/* Variables and functions */

__attribute__((used)) static int
nouveau_fantog_get(struct nouveau_therm *therm)
{
	struct nouveau_therm_priv *tpriv = (void *)therm;
	struct nouveau_fantog_priv *priv = (void *)tpriv->fan;
	return priv->percent;
}