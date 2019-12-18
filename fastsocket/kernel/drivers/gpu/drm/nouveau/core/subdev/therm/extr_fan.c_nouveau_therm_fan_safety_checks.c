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
struct nouveau_therm_priv {TYPE_1__* fan; } ;
struct nouveau_therm {int dummy; } ;
struct TYPE_4__ {int min_duty; int max_duty; } ;
struct TYPE_3__ {TYPE_2__ bios; } ;

/* Variables and functions */

__attribute__((used)) static void
nouveau_therm_fan_safety_checks(struct nouveau_therm *therm)
{
	struct nouveau_therm_priv *priv = (void *)therm;

	if (priv->fan->bios.min_duty > 100)
		priv->fan->bios.min_duty = 100;
	if (priv->fan->bios.max_duty > 100)
		priv->fan->bios.max_duty = 100;

	if (priv->fan->bios.min_duty > priv->fan->bios.max_duty)
		priv->fan->bios.min_duty = priv->fan->bios.max_duty;
}