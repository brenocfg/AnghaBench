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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u8 ;
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
 int nv_rd32 (struct nouveau_therm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_wr32 (struct nouveau_therm*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct nouveau_therm*) ; 

__attribute__((used)) static void
nv50_therm_threshold_hyst_emulation(struct nouveau_therm *therm,
				   uint32_t thrs_reg, u8 status_bit,
				   const struct nvbios_therm_threshold *thrs,
				   enum nouveau_therm_thrs thrs_name)
{
	enum nouveau_therm_thrs_direction direction;
	enum nouveau_therm_thrs_state prev_state, new_state;
	int temp, cur;

	prev_state = nouveau_therm_sensor_get_threshold_state(therm, thrs_name);
	temp = nv_rd32(therm, thrs_reg);

	/* program the next threshold */
	if (temp == thrs->temp) {
		nv_wr32(therm, thrs_reg, thrs->temp - thrs->hysteresis);
		new_state = NOUVEAU_THERM_THRS_HIGHER;
	} else {
		nv_wr32(therm, thrs_reg, thrs->temp);
		new_state = NOUVEAU_THERM_THRS_LOWER;
	}

	/* fix the state (in case someone reprogrammed the alarms) */
	cur = therm->temp_get(therm);
	if (new_state == NOUVEAU_THERM_THRS_LOWER && cur > thrs->temp)
		new_state = NOUVEAU_THERM_THRS_HIGHER;
	else if (new_state == NOUVEAU_THERM_THRS_HIGHER &&
		cur < thrs->temp - thrs->hysteresis)
		new_state = NOUVEAU_THERM_THRS_LOWER;
	nouveau_therm_sensor_set_threshold_state(therm, thrs_name, new_state);

	/* find the direction */
	if (prev_state < new_state)
		direction = NOUVEAU_THERM_THRS_RISING;
	else if (prev_state > new_state)
		direction = NOUVEAU_THERM_THRS_FALLING;
	else
		return;

	/* advertise a change in direction */
	nouveau_therm_sensor_event(therm, thrs_name, direction);
}