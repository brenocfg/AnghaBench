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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct nouveau_therm_priv {TYPE_2__* fan; } ;
struct nouveau_therm {scalar_t__ (* temp_get ) (struct nouveau_therm*) ;} ;
struct TYPE_3__ {scalar_t__ linear_min_temp; scalar_t__ linear_max_temp; int min_duty; int max_duty; } ;
struct TYPE_4__ {TYPE_1__ bios; } ;

/* Variables and functions */
 scalar_t__ stub1 (struct nouveau_therm*) ; 

__attribute__((used)) static int
nouveau_therm_update_linear(struct nouveau_therm *therm)
{
	struct nouveau_therm_priv *priv = (void *)therm;
	u8  linear_min_temp = priv->fan->bios.linear_min_temp;
	u8  linear_max_temp = priv->fan->bios.linear_max_temp;
	u8  temp = therm->temp_get(therm);
	u16 duty;

	/* handle the non-linear part first */
	if (temp < linear_min_temp)
		return priv->fan->bios.min_duty;
	else if (temp > linear_max_temp)
		return priv->fan->bios.max_duty;

	/* we are in the linear zone */
	duty  = (temp - linear_min_temp);
	duty *= (priv->fan->bios.max_duty - priv->fan->bios.min_duty);
	duty /= (linear_max_temp - linear_min_temp);
	duty += priv->fan->bios.min_duty;

	return duty;
}