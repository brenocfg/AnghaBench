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
struct nouveau_therm_priv {scalar_t__ fan; } ;
struct nouveau_therm {int /*<<< orphan*/  (* pwm_ctrl ) (struct nouveau_therm*,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  line; } ;
struct nouveau_fantog_priv {TYPE_1__ func; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_fantog_update (struct nouveau_fantog_priv*,int) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_therm*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nouveau_fantog_set(struct nouveau_therm *therm, int percent)
{
	struct nouveau_therm_priv *tpriv = (void *)therm;
	struct nouveau_fantog_priv *priv = (void *)tpriv->fan;
	if (therm->pwm_ctrl)
		therm->pwm_ctrl(therm, priv->func.line, false);
	nouveau_fantog_update(priv, percent);
	return 0;
}