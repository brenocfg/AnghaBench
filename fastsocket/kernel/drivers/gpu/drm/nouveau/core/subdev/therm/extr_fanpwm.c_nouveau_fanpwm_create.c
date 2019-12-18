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
typedef  int /*<<< orphan*/  u32 ;
struct nouveau_therm_priv {TYPE_1__* fan; } ;
struct nouveau_therm {int (* pwm_get ) (struct nouveau_therm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  pwm_ctrl; } ;
struct dcb_gpio_func {int /*<<< orphan*/  line; int /*<<< orphan*/  param; } ;
struct TYPE_2__ {char* type; int /*<<< orphan*/  set; int /*<<< orphan*/  get; } ;
struct nouveau_fanpwm_priv {struct dcb_gpio_func func; TYPE_1__ base; } ;
struct nouveau_device {int /*<<< orphan*/  cfgopt; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nouveau_fanpwm_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_boolopt (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_fanpwm_get ; 
 int /*<<< orphan*/  nouveau_fanpwm_set ; 
 struct nouveau_device* nv_device (struct nouveau_therm*) ; 
 int stub1 (struct nouveau_therm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
nouveau_fanpwm_create(struct nouveau_therm *therm, struct dcb_gpio_func *func)
{
	struct nouveau_device *device = nv_device(therm);
	struct nouveau_therm_priv *tpriv = (void *)therm;
	struct nouveau_fanpwm_priv *priv;
	u32 divs, duty;

	if (!nouveau_boolopt(device->cfgopt, "NvFanPWM", func->param) ||
	    !therm->pwm_ctrl ||
	     therm->pwm_get(therm, func->line, &divs, &duty) == -ENODEV)
		return -ENODEV;

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	tpriv->fan = &priv->base;
	if (!priv)
		return -ENOMEM;

	priv->base.type = "PWM";
	priv->base.get = nouveau_fanpwm_get;
	priv->base.set = nouveau_fanpwm_set;
	priv->func = *func;
	return 0;
}