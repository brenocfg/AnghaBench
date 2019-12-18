#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int /*<<< orphan*/  fan_sense; int /*<<< orphan*/  temp_get; int /*<<< orphan*/  pwm_clock; int /*<<< orphan*/  pwm_set; int /*<<< orphan*/  pwm_get; int /*<<< orphan*/  pwm_ctrl; } ;
struct TYPE_4__ {int /*<<< orphan*/  program_alarms; } ;
struct TYPE_5__ {TYPE_3__ base; TYPE_1__ sensor; } ;
struct nvd0_therm_priv {TYPE_2__ base; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int nouveau_therm_create (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,struct nvd0_therm_priv**) ; 
 int nouveau_therm_preinit (TYPE_3__*) ; 
 int /*<<< orphan*/  nouveau_therm_program_alarms_polling ; 
 int /*<<< orphan*/  nv50_temp_get ; 
 struct nouveau_object* nv_object (struct nvd0_therm_priv*) ; 
 int /*<<< orphan*/  nva3_therm_fan_sense ; 
 int /*<<< orphan*/  nvd0_fan_pwm_clock ; 
 int /*<<< orphan*/  nvd0_fan_pwm_ctrl ; 
 int /*<<< orphan*/  nvd0_fan_pwm_get ; 
 int /*<<< orphan*/  nvd0_fan_pwm_set ; 

__attribute__((used)) static int
nvd0_therm_ctor(struct nouveau_object *parent,
		struct nouveau_object *engine,
		struct nouveau_oclass *oclass, void *data, u32 size,
		struct nouveau_object **pobject)
{
	struct nvd0_therm_priv *priv;
	int ret;

	ret = nouveau_therm_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	priv->base.base.pwm_ctrl = nvd0_fan_pwm_ctrl;
	priv->base.base.pwm_get = nvd0_fan_pwm_get;
	priv->base.base.pwm_set = nvd0_fan_pwm_set;
	priv->base.base.pwm_clock = nvd0_fan_pwm_clock;
	priv->base.base.temp_get = nv50_temp_get;
	priv->base.base.fan_sense = nva3_therm_fan_sense;
	priv->base.sensor.program_alarms = nouveau_therm_program_alarms_polling;
	return nouveau_therm_preinit(&priv->base.base);
}