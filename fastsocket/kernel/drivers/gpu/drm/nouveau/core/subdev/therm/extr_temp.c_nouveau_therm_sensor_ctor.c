#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  therm_poll_alarm; } ;
struct nouveau_therm_priv {int /*<<< orphan*/  bios_sensor; TYPE_1__ sensor; } ;
struct nouveau_therm {int dummy; } ;
struct nouveau_bios {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVBIOS_THERM_DOMAIN_CORE ; 
 int /*<<< orphan*/  alarm_timer_callback ; 
 int /*<<< orphan*/  nouveau_alarm_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nouveau_bios* nouveau_bios (struct nouveau_therm*) ; 
 int /*<<< orphan*/  nouveau_therm_temp_safety_checks (struct nouveau_therm*) ; 
 int /*<<< orphan*/  nouveau_therm_temp_set_defaults (struct nouveau_therm*) ; 
 int /*<<< orphan*/  nv_error (struct nouveau_therm*,char*) ; 
 scalar_t__ nvbios_therm_sensor_parse (struct nouveau_bios*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
nouveau_therm_sensor_ctor(struct nouveau_therm *therm)
{
	struct nouveau_therm_priv *priv = (void *)therm;
	struct nouveau_bios *bios = nouveau_bios(therm);

	nouveau_alarm_init(&priv->sensor.therm_poll_alarm, alarm_timer_callback);

	nouveau_therm_temp_set_defaults(therm);
	if (nvbios_therm_sensor_parse(bios, NVBIOS_THERM_DOMAIN_CORE,
				      &priv->bios_sensor))
		nv_error(therm, "nvbios_therm_sensor_parse failed\n");
	nouveau_therm_temp_safety_checks(therm);

	return 0;
}