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
struct TYPE_2__ {int /*<<< orphan*/  (* program_alarms ) (struct nouveau_therm*) ;} ;
struct nouveau_therm_priv {scalar_t__ suspend; TYPE_1__ sensor; int /*<<< orphan*/  mode; } ;
struct nouveau_therm {int /*<<< orphan*/  base; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int nouveau_subdev_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_therm_fan_mode (struct nouveau_therm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_therm*) ; 

int
_nouveau_therm_init(struct nouveau_object *object)
{
	struct nouveau_therm *therm = (void *)object;
	struct nouveau_therm_priv *priv = (void *)therm;
	int ret;

	ret = nouveau_subdev_init(&therm->base);
	if (ret)
		return ret;

	if (priv->suspend >= 0)
		nouveau_therm_fan_mode(therm, priv->mode);
	priv->sensor.program_alarms(therm);
	return 0;
}