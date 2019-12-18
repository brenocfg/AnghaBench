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
struct nouveau_therm_priv {TYPE_1__* fan; } ;
struct nouveau_therm {int dummy; } ;
struct nouveau_gpio {int (* find ) (struct nouveau_gpio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct dcb_gpio_func*) ;} ;
struct nouveau_bios {int dummy; } ;
struct dcb_gpio_func {int* log; int /*<<< orphan*/  func; } ;
struct TYPE_2__ {int /*<<< orphan*/  bios; int /*<<< orphan*/  perf; int /*<<< orphan*/  lock; int /*<<< orphan*/  alarm; struct nouveau_therm* parent; struct dcb_gpio_func tach; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCB_GPIO_FAN ; 
 int /*<<< orphan*/  DCB_GPIO_FAN_SENSE ; 
 int DCB_GPIO_LOG_DIR_IN ; 
 int /*<<< orphan*/  DCB_GPIO_UNUSED ; 
 int EINVAL ; 
 int /*<<< orphan*/  nouveau_alarm_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nouveau_bios* nouveau_bios (struct nouveau_therm*) ; 
 int /*<<< orphan*/  nouveau_fan_alarm ; 
 int nouveau_fannil_create (struct nouveau_therm*) ; 
 int nouveau_fanpwm_create (struct nouveau_therm*,struct dcb_gpio_func*) ; 
 int nouveau_fantog_create (struct nouveau_therm*,struct dcb_gpio_func*) ; 
 struct nouveau_gpio* nouveau_gpio (struct nouveau_therm*) ; 
 int /*<<< orphan*/  nouveau_therm_fan_safety_checks (struct nouveau_therm*) ; 
 int /*<<< orphan*/  nouveau_therm_fan_set_defaults (struct nouveau_therm*) ; 
 int /*<<< orphan*/  nv_debug (struct nouveau_therm*,char*) ; 
 int /*<<< orphan*/  nv_error (struct nouveau_therm*,char*) ; 
 int /*<<< orphan*/  nv_info (struct nouveau_therm*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvbios_perf_fan_parse (struct nouveau_bios*,int /*<<< orphan*/ *) ; 
 scalar_t__ nvbios_therm_fan_parse (struct nouveau_bios*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int stub1 (struct nouveau_gpio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct dcb_gpio_func*) ; 
 int stub2 (struct nouveau_gpio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct dcb_gpio_func*) ; 

int
nouveau_therm_fan_ctor(struct nouveau_therm *therm)
{
	struct nouveau_therm_priv *priv = (void *)therm;
	struct nouveau_gpio *gpio = nouveau_gpio(therm);
	struct nouveau_bios *bios = nouveau_bios(therm);
	struct dcb_gpio_func func;
	int ret;

	/* attempt to locate a drivable fan, and determine control method */
	ret = gpio->find(gpio, 0, DCB_GPIO_FAN, 0xff, &func);
	if (ret == 0) {
		if (func.log[0] & DCB_GPIO_LOG_DIR_IN) {
			nv_debug(therm, "GPIO_FAN is in input mode\n");
			ret = -EINVAL;
		} else {
			ret = nouveau_fanpwm_create(therm, &func);
			if (ret != 0)
				ret = nouveau_fantog_create(therm, &func);
		}
	}

	/* no controllable fan found, create a dummy fan module */
	if (ret != 0) {
		ret = nouveau_fannil_create(therm);
		if (ret)
			return ret;
	}

	nv_info(therm, "FAN control: %s\n", priv->fan->type);

	/* attempt to detect a tachometer connection */
	ret = gpio->find(gpio, 0, DCB_GPIO_FAN_SENSE, 0xff, &priv->fan->tach);
	if (ret)
		priv->fan->tach.func = DCB_GPIO_UNUSED;

	/* initialise fan bump/slow update handling */
	priv->fan->parent = therm;
	nouveau_alarm_init(&priv->fan->alarm, nouveau_fan_alarm);
	spin_lock_init(&priv->fan->lock);

	/* other random init... */
	nouveau_therm_fan_set_defaults(therm);
	nvbios_perf_fan_parse(bios, &priv->fan->perf);
	if (nvbios_therm_fan_parse(bios, &priv->fan->bios))
		nv_error(therm, "parsing the thermal table failed\n");
	nouveau_therm_fan_safety_checks(therm);
	return 0;
}