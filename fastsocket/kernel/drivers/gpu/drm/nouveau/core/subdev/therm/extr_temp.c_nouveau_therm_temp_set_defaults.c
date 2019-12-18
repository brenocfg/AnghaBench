#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int temp; int hysteresis; } ;
struct TYPE_8__ {int temp; int hysteresis; } ;
struct TYPE_7__ {int temp; int hysteresis; } ;
struct TYPE_6__ {int temp; int hysteresis; } ;
struct TYPE_10__ {TYPE_4__ thrs_shutdown; TYPE_3__ thrs_critical; TYPE_2__ thrs_down_clock; TYPE_1__ thrs_fan_boost; scalar_t__ offset_constant; } ;
struct nouveau_therm_priv {TYPE_5__ bios_sensor; } ;
struct nouveau_therm {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
nouveau_therm_temp_set_defaults(struct nouveau_therm *therm)
{
	struct nouveau_therm_priv *priv = (void *)therm;

	priv->bios_sensor.offset_constant = 0;

	priv->bios_sensor.thrs_fan_boost.temp = 90;
	priv->bios_sensor.thrs_fan_boost.hysteresis = 3;

	priv->bios_sensor.thrs_down_clock.temp = 95;
	priv->bios_sensor.thrs_down_clock.hysteresis = 3;

	priv->bios_sensor.thrs_critical.temp = 105;
	priv->bios_sensor.thrs_critical.hysteresis = 5;

	priv->bios_sensor.thrs_shutdown.temp = 135;
	priv->bios_sensor.thrs_shutdown.hysteresis = 5; /*not that it matters */
}