#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  (* program_alarms ) (struct nouveau_therm*) ;} ;
struct TYPE_14__ {int temp; int hysteresis; } ;
struct TYPE_13__ {int temp; int hysteresis; } ;
struct TYPE_12__ {int temp; int hysteresis; } ;
struct TYPE_11__ {int temp; int hysteresis; } ;
struct TYPE_15__ {TYPE_6__ thrs_shutdown; TYPE_5__ thrs_critical; TYPE_4__ thrs_down_clock; TYPE_3__ thrs_fan_boost; } ;
struct nouveau_therm_priv {TYPE_8__ sensor; TYPE_7__ bios_sensor; TYPE_2__* fan; } ;
struct nouveau_therm {int dummy; } ;
typedef  enum nouveau_therm_attr_type { ____Placeholder_nouveau_therm_attr_type } nouveau_therm_attr_type ;
struct TYPE_9__ {int max_duty; int min_duty; } ;
struct TYPE_10__ {TYPE_1__ bios; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NOUVEAU_THERM_ATTR_FAN_MAX_DUTY 138 
#define  NOUVEAU_THERM_ATTR_FAN_MIN_DUTY 137 
#define  NOUVEAU_THERM_ATTR_FAN_MODE 136 
#define  NOUVEAU_THERM_ATTR_THRS_CRITICAL 135 
#define  NOUVEAU_THERM_ATTR_THRS_CRITICAL_HYST 134 
#define  NOUVEAU_THERM_ATTR_THRS_DOWN_CLK 133 
#define  NOUVEAU_THERM_ATTR_THRS_DOWN_CLK_HYST 132 
#define  NOUVEAU_THERM_ATTR_THRS_FAN_BOOST 131 
#define  NOUVEAU_THERM_ATTR_THRS_FAN_BOOST_HYST 130 
#define  NOUVEAU_THERM_ATTR_THRS_SHUTDOWN 129 
#define  NOUVEAU_THERM_ATTR_THRS_SHUTDOWN_HYST 128 
 int nouveau_therm_fan_mode (struct nouveau_therm*,int) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_therm*) ; 
 int /*<<< orphan*/  stub2 (struct nouveau_therm*) ; 
 int /*<<< orphan*/  stub3 (struct nouveau_therm*) ; 
 int /*<<< orphan*/  stub4 (struct nouveau_therm*) ; 
 int /*<<< orphan*/  stub5 (struct nouveau_therm*) ; 
 int /*<<< orphan*/  stub6 (struct nouveau_therm*) ; 
 int /*<<< orphan*/  stub7 (struct nouveau_therm*) ; 
 int /*<<< orphan*/  stub8 (struct nouveau_therm*) ; 

int
nouveau_therm_attr_set(struct nouveau_therm *therm,
		       enum nouveau_therm_attr_type type, int value)
{
	struct nouveau_therm_priv *priv = (void *)therm;

	switch (type) {
	case NOUVEAU_THERM_ATTR_FAN_MIN_DUTY:
		if (value < 0)
			value = 0;
		if (value > priv->fan->bios.max_duty)
			value = priv->fan->bios.max_duty;
		priv->fan->bios.min_duty = value;
		return 0;
	case NOUVEAU_THERM_ATTR_FAN_MAX_DUTY:
		if (value < 0)
			value = 0;
		if (value < priv->fan->bios.min_duty)
			value = priv->fan->bios.min_duty;
		priv->fan->bios.max_duty = value;
		return 0;
	case NOUVEAU_THERM_ATTR_FAN_MODE:
		return nouveau_therm_fan_mode(therm, value);
	case NOUVEAU_THERM_ATTR_THRS_FAN_BOOST:
		priv->bios_sensor.thrs_fan_boost.temp = value;
		priv->sensor.program_alarms(therm);
		return 0;
	case NOUVEAU_THERM_ATTR_THRS_FAN_BOOST_HYST:
		priv->bios_sensor.thrs_fan_boost.hysteresis = value;
		priv->sensor.program_alarms(therm);
		return 0;
	case NOUVEAU_THERM_ATTR_THRS_DOWN_CLK:
		priv->bios_sensor.thrs_down_clock.temp = value;
		priv->sensor.program_alarms(therm);
		return 0;
	case NOUVEAU_THERM_ATTR_THRS_DOWN_CLK_HYST:
		priv->bios_sensor.thrs_down_clock.hysteresis = value;
		priv->sensor.program_alarms(therm);
		return 0;
	case NOUVEAU_THERM_ATTR_THRS_CRITICAL:
		priv->bios_sensor.thrs_critical.temp = value;
		priv->sensor.program_alarms(therm);
		return 0;
	case NOUVEAU_THERM_ATTR_THRS_CRITICAL_HYST:
		priv->bios_sensor.thrs_critical.hysteresis = value;
		priv->sensor.program_alarms(therm);
		return 0;
	case NOUVEAU_THERM_ATTR_THRS_SHUTDOWN:
		priv->bios_sensor.thrs_shutdown.temp = value;
		priv->sensor.program_alarms(therm);
		return 0;
	case NOUVEAU_THERM_ATTR_THRS_SHUTDOWN_HYST:
		priv->bios_sensor.thrs_shutdown.hysteresis = value;
		priv->sensor.program_alarms(therm);
		return 0;
	}

	return -EINVAL;
}