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
struct nouveau_therm_priv {int /*<<< orphan*/  fan; } ;
struct nouveau_therm {int dummy; } ;

/* Variables and functions */
 int nouveau_fan_update (int /*<<< orphan*/ ,int,int) ; 

int
nouveau_therm_fan_set(struct nouveau_therm *therm, bool immediate, int percent)
{
	struct nouveau_therm_priv *priv = (void *)therm;
	return nouveau_fan_update(priv->fan, immediate, percent);
}