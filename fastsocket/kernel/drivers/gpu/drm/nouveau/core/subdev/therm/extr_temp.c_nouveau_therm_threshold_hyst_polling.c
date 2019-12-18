#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nvbios_therm_threshold {int temp; int hysteresis; } ;
struct nouveau_therm {int (* temp_get ) (struct nouveau_therm*) ;} ;
typedef  enum nouveau_therm_thrs_state { ____Placeholder_nouveau_therm_thrs_state } nouveau_therm_thrs_state ;
typedef  enum nouveau_therm_thrs_direction { ____Placeholder_nouveau_therm_thrs_direction } nouveau_therm_thrs_direction ;
typedef  enum nouveau_therm_thrs { ____Placeholder_nouveau_therm_thrs } nouveau_therm_thrs ;

/* Variables and functions */
 int NOUVEAU_THERM_THRS_FALLING ; 
 int NOUVEAU_THERM_THRS_HIGHER ; 
 int NOUVEAU_THERM_THRS_LOWER ; 
 int NOUVEAU_THERM_THRS_RISING ; 
 int /*<<< orphan*/  nouveau_therm_sensor_event (struct nouveau_therm*,int,int) ; 
 int nouveau_therm_sensor_get_threshold_state (struct nouveau_therm*,int) ; 
 int /*<<< orphan*/  nouveau_therm_sensor_set_threshold_state (struct nouveau_therm*,int,int) ; 
 int stub1 (struct nouveau_therm*) ; 

__attribute__((used)) static void
nouveau_therm_threshold_hyst_polling(struct nouveau_therm *therm,
				   const struct nvbios_therm_threshold *thrs,
				   enum nouveau_therm_thrs thrs_name)
{
	enum nouveau_therm_thrs_direction direction;
	enum nouveau_therm_thrs_state prev_state, new_state;
	int temp = therm->temp_get(therm);

	prev_state = nouveau_therm_sensor_get_threshold_state(therm, thrs_name);

	if (temp >= thrs->temp && prev_state == NOUVEAU_THERM_THRS_LOWER) {
		direction = NOUVEAU_THERM_THRS_RISING;
		new_state = NOUVEAU_THERM_THRS_HIGHER;
	} else if (temp <= thrs->temp - thrs->hysteresis &&
			prev_state == NOUVEAU_THERM_THRS_HIGHER) {
		direction = NOUVEAU_THERM_THRS_FALLING;
		new_state = NOUVEAU_THERM_THRS_LOWER;
	} else
		return; /* nothing to do */

	nouveau_therm_sensor_set_threshold_state(therm, thrs_name, new_state);
	nouveau_therm_sensor_event(therm, thrs_name, direction);
}