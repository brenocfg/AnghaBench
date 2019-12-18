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
struct TYPE_4__ {int /*<<< orphan*/  attr_set; int /*<<< orphan*/  attr_get; int /*<<< orphan*/  fan_sense; int /*<<< orphan*/  fan_set; int /*<<< orphan*/  fan_get; } ;
struct TYPE_3__ {int /*<<< orphan*/  alarm_program_lock; } ;
struct nouveau_therm_priv {int mode; int suspend; TYPE_2__ base; TYPE_1__ sensor; int /*<<< orphan*/  lock; int /*<<< orphan*/  alarm; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_alarm_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nouveau_subdev_create_ (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,int /*<<< orphan*/ ,char*,char*,int,void**) ; 
 int /*<<< orphan*/  nouveau_therm_alarm ; 
 int /*<<< orphan*/  nouveau_therm_attr_get ; 
 int /*<<< orphan*/  nouveau_therm_attr_set ; 
 int /*<<< orphan*/  nouveau_therm_fan_sense ; 
 int /*<<< orphan*/  nouveau_therm_fan_user_get ; 
 int /*<<< orphan*/  nouveau_therm_fan_user_set ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int
nouveau_therm_create_(struct nouveau_object *parent,
		      struct nouveau_object *engine,
		      struct nouveau_oclass *oclass,
		      int length, void **pobject)
{
	struct nouveau_therm_priv *priv;
	int ret;

	ret = nouveau_subdev_create_(parent, engine, oclass, 0, "PTHERM",
				     "therm", length, pobject);
	priv = *pobject;
	if (ret)
		return ret;

	nouveau_alarm_init(&priv->alarm, nouveau_therm_alarm);
	spin_lock_init(&priv->lock);
	spin_lock_init(&priv->sensor.alarm_program_lock);

	priv->base.fan_get = nouveau_therm_fan_user_get;
	priv->base.fan_set = nouveau_therm_fan_user_set;
	priv->base.fan_sense = nouveau_therm_fan_sense;
	priv->base.attr_get = nouveau_therm_attr_get;
	priv->base.attr_set = nouveau_therm_attr_set;
	priv->mode = priv->suspend = -1; /* undefined */
	return 0;
}