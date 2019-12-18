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
struct nouveau_therm_priv {TYPE_2__* fan; } ;
struct nouveau_therm {int dummy; } ;
struct TYPE_3__ {int max_duty; int bump_period; int slow_down_period; int linear_min_temp; int linear_max_temp; scalar_t__ min_duty; scalar_t__ pwm_freq; } ;
struct TYPE_4__ {TYPE_1__ bios; } ;

/* Variables and functions */

__attribute__((used)) static void
nouveau_therm_fan_set_defaults(struct nouveau_therm *therm)
{
	struct nouveau_therm_priv *priv = (void *)therm;

	priv->fan->bios.pwm_freq = 0;
	priv->fan->bios.min_duty = 0;
	priv->fan->bios.max_duty = 100;
	priv->fan->bios.bump_period = 500;
	priv->fan->bios.slow_down_period = 2000;
	priv->fan->bios.linear_min_temp = 40;
	priv->fan->bios.linear_max_temp = 85;
}