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
struct nouveau_timer {int /*<<< orphan*/  (* alarm ) (struct nouveau_timer*,unsigned long long,TYPE_3__*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  head; } ;
struct nouveau_therm_priv {int mode; int /*<<< orphan*/  lock; TYPE_3__ alarm; TYPE_2__* fan; } ;
struct nouveau_therm {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  nr_fan_trip; } ;
struct TYPE_5__ {TYPE_1__ bios; } ;

/* Variables and functions */
#define  NOUVEAU_THERM_CTRL_AUTO 130 
#define  NOUVEAU_THERM_CTRL_MANUAL 129 
#define  NOUVEAU_THERM_CTRL_NONE 128 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int nouveau_therm_fan_get (struct nouveau_therm*) ; 
 int /*<<< orphan*/  nouveau_therm_fan_set (struct nouveau_therm*,int,int) ; 
 int nouveau_therm_update_linear (struct nouveau_therm*) ; 
 int nouveau_therm_update_trip (struct nouveau_therm*) ; 
 struct nouveau_timer* nouveau_timer (struct nouveau_therm*) ; 
 int /*<<< orphan*/  nv_debug (struct nouveau_therm*,char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_timer*,unsigned long long,TYPE_3__*) ; 

__attribute__((used)) static void
nouveau_therm_update(struct nouveau_therm *therm, int mode)
{
	struct nouveau_timer *ptimer = nouveau_timer(therm);
	struct nouveau_therm_priv *priv = (void *)therm;
	unsigned long flags;
	int duty;

	spin_lock_irqsave(&priv->lock, flags);
	if (mode < 0)
		mode = priv->mode;
	priv->mode = mode;

	switch (mode) {
	case NOUVEAU_THERM_CTRL_MANUAL:
		duty = nouveau_therm_fan_get(therm);
		if (duty < 0)
			duty = 100;
		break;
	case NOUVEAU_THERM_CTRL_AUTO:
		if (priv->fan->bios.nr_fan_trip)
			duty = nouveau_therm_update_trip(therm);
		else
			duty = nouveau_therm_update_linear(therm);
		break;
	case NOUVEAU_THERM_CTRL_NONE:
	default:
		goto done;
	}

	nv_debug(therm, "FAN target request: %d%%\n", duty);
	nouveau_therm_fan_set(therm, (mode != NOUVEAU_THERM_CTRL_AUTO), duty);

done:
	if (list_empty(&priv->alarm.head) && (mode == NOUVEAU_THERM_CTRL_AUTO))
		ptimer->alarm(ptimer, 1000000000ULL, &priv->alarm);
	spin_unlock_irqrestore(&priv->lock, flags);
}