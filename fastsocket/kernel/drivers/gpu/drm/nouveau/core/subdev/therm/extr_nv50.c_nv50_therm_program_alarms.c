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
struct TYPE_10__ {int hysteresis; int temp; } ;
struct TYPE_9__ {int temp; int /*<<< orphan*/  hysteresis; } ;
struct TYPE_8__ {int temp; int /*<<< orphan*/  hysteresis; } ;
struct TYPE_7__ {int temp; int /*<<< orphan*/  hysteresis; } ;
struct nvbios_therm_sensor {TYPE_5__ thrs_shutdown; TYPE_4__ thrs_critical; TYPE_3__ thrs_down_clock; TYPE_2__ thrs_fan_boost; } ;
struct TYPE_6__ {int /*<<< orphan*/  alarm_program_lock; } ;
struct nouveau_therm_priv {TYPE_1__ sensor; struct nvbios_therm_sensor bios_sensor; } ;
struct nouveau_therm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv_info (struct nouveau_therm*,char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nouveau_therm*,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
nv50_therm_program_alarms(struct nouveau_therm *therm)
{
	struct nouveau_therm_priv *priv = (void *)therm;
	struct nvbios_therm_sensor *sensor = &priv->bios_sensor;
	unsigned long flags;

	spin_lock_irqsave(&priv->sensor.alarm_program_lock, flags);

	/* enable RISING and FALLING IRQs for shutdown, THRS 0, 1, 2 and 4 */
	nv_wr32(therm, 0x20000, 0x000003ff);

	/* shutdown: The computer should be shutdown when reached */
	nv_wr32(therm, 0x20484, sensor->thrs_shutdown.hysteresis);
	nv_wr32(therm, 0x20480, sensor->thrs_shutdown.temp);

	/* THRS_1 : fan boost*/
	nv_wr32(therm, 0x204c4, sensor->thrs_fan_boost.temp);

	/* THRS_2 : critical */
	nv_wr32(therm, 0x204c0, sensor->thrs_critical.temp);

	/* THRS_4 : down clock */
	nv_wr32(therm, 0x20414, sensor->thrs_down_clock.temp);
	spin_unlock_irqrestore(&priv->sensor.alarm_program_lock, flags);

	nv_info(therm,
		"Programmed thresholds [ %d(%d), %d(%d), %d(%d), %d(%d) ]\n",
		sensor->thrs_fan_boost.temp, sensor->thrs_fan_boost.hysteresis,
		sensor->thrs_down_clock.temp,
		sensor->thrs_down_clock.hysteresis,
		sensor->thrs_critical.temp, sensor->thrs_critical.hysteresis,
		sensor->thrs_shutdown.temp, sensor->thrs_shutdown.hysteresis);

}