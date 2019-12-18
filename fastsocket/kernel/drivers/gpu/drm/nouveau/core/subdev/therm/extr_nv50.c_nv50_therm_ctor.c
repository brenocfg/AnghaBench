#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_9__ {int /*<<< orphan*/  temp_get; int /*<<< orphan*/  pwm_clock; int /*<<< orphan*/  pwm_set; int /*<<< orphan*/  pwm_get; int /*<<< orphan*/  pwm_ctrl; } ;
struct TYPE_6__ {int /*<<< orphan*/  program_alarms; } ;
struct TYPE_7__ {TYPE_4__ base; TYPE_1__ sensor; } ;
struct nv50_therm_priv {TYPE_2__ base; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  intr; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOUVEAU_THERM_THRS_CRITICAL ; 
 int /*<<< orphan*/  NOUVEAU_THERM_THRS_DOWNCLOCK ; 
 int /*<<< orphan*/  NOUVEAU_THERM_THRS_FANBOOST ; 
 int /*<<< orphan*/  NOUVEAU_THERM_THRS_LOWER ; 
 int /*<<< orphan*/  NOUVEAU_THERM_THRS_SHUTDOWN ; 
 int nouveau_therm_create (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,struct nv50_therm_priv**) ; 
 int nouveau_therm_preinit (TYPE_4__*) ; 
 int /*<<< orphan*/  nouveau_therm_sensor_set_threshold_state (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv50_fan_pwm_clock ; 
 int /*<<< orphan*/  nv50_fan_pwm_ctrl ; 
 int /*<<< orphan*/  nv50_fan_pwm_get ; 
 int /*<<< orphan*/  nv50_fan_pwm_set ; 
 int /*<<< orphan*/  nv50_temp_get ; 
 int /*<<< orphan*/  nv50_therm_intr ; 
 int /*<<< orphan*/  nv50_therm_program_alarms ; 
 struct nouveau_object* nv_object (struct nv50_therm_priv*) ; 
 TYPE_3__* nv_subdev (struct nv50_therm_priv*) ; 

__attribute__((used)) static int
nv50_therm_ctor(struct nouveau_object *parent,
		struct nouveau_object *engine,
		struct nouveau_oclass *oclass, void *data, u32 size,
		struct nouveau_object **pobject)
{
	struct nv50_therm_priv *priv;
	int ret;

	ret = nouveau_therm_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	priv->base.base.pwm_ctrl = nv50_fan_pwm_ctrl;
	priv->base.base.pwm_get = nv50_fan_pwm_get;
	priv->base.base.pwm_set = nv50_fan_pwm_set;
	priv->base.base.pwm_clock = nv50_fan_pwm_clock;
	priv->base.base.temp_get = nv50_temp_get;
	priv->base.sensor.program_alarms = nv50_therm_program_alarms;
	nv_subdev(priv)->intr = nv50_therm_intr;

	/* init the thresholds */
	nouveau_therm_sensor_set_threshold_state(&priv->base.base,
						 NOUVEAU_THERM_THRS_SHUTDOWN,
						 NOUVEAU_THERM_THRS_LOWER);
	nouveau_therm_sensor_set_threshold_state(&priv->base.base,
						 NOUVEAU_THERM_THRS_FANBOOST,
						 NOUVEAU_THERM_THRS_LOWER);
	nouveau_therm_sensor_set_threshold_state(&priv->base.base,
						 NOUVEAU_THERM_THRS_CRITICAL,
						 NOUVEAU_THERM_THRS_LOWER);
	nouveau_therm_sensor_set_threshold_state(&priv->base.base,
						 NOUVEAU_THERM_THRS_DOWNCLOCK,
						 NOUVEAU_THERM_THRS_LOWER);

	return nouveau_therm_preinit(&priv->base.base);
}