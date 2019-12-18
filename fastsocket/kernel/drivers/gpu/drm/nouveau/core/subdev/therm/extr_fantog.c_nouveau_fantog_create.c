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
struct dcb_gpio_func {int dummy; } ;
struct TYPE_2__ {char* type; int /*<<< orphan*/  set; int /*<<< orphan*/  get; } ;
struct nouveau_fantog_priv {int period_us; int percent; int /*<<< orphan*/  lock; struct dcb_gpio_func func; int /*<<< orphan*/  alarm; TYPE_1__ base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nouveau_fantog_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_alarm_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_fantog_alarm ; 
 int /*<<< orphan*/  nouveau_fantog_get ; 
 int /*<<< orphan*/  nouveau_fantog_set ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int
nouveau_fantog_create(struct nouveau_therm *therm, struct dcb_gpio_func *func)
{
	struct nouveau_therm_priv *tpriv = (void *)therm;
	struct nouveau_fantog_priv *priv;

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	tpriv->fan = &priv->base;
	if (!priv)
		return -ENOMEM;

	priv->base.type = "toggle";
	priv->base.get = nouveau_fantog_get;
	priv->base.set = nouveau_fantog_set;
	nouveau_alarm_init(&priv->alarm, nouveau_fantog_alarm);
	priv->period_us = 100000; /* 10Hz */
	priv->percent = 100;
	priv->func = *func;
	spin_lock_init(&priv->lock);
	return 0;
}