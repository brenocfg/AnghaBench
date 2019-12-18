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
struct TYPE_2__ {int* alarm_state; } ;
struct nouveau_therm_priv {TYPE_1__ sensor; } ;
struct nouveau_therm {int dummy; } ;
typedef  enum nouveau_therm_thrs_state { ____Placeholder_nouveau_therm_thrs_state } nouveau_therm_thrs_state ;
typedef  enum nouveau_therm_thrs { ____Placeholder_nouveau_therm_thrs } nouveau_therm_thrs ;

/* Variables and functions */

enum nouveau_therm_thrs_state
nouveau_therm_sensor_get_threshold_state(struct nouveau_therm *therm,
					 enum nouveau_therm_thrs thrs)
{
	struct nouveau_therm_priv *priv = (void *)therm;
	return priv->sensor.alarm_state[thrs];
}