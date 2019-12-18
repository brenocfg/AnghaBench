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
struct nouveau_therm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOUVEAU_THERM_CTRL_NONE ; 
 int /*<<< orphan*/  nouveau_therm_fan_ctor (struct nouveau_therm*) ; 
 int /*<<< orphan*/  nouveau_therm_fan_mode (struct nouveau_therm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_therm_ic_ctor (struct nouveau_therm*) ; 
 int /*<<< orphan*/  nouveau_therm_sensor_ctor (struct nouveau_therm*) ; 
 int /*<<< orphan*/  nouveau_therm_sensor_preinit (struct nouveau_therm*) ; 

int
nouveau_therm_preinit(struct nouveau_therm *therm)
{
	nouveau_therm_sensor_ctor(therm);
	nouveau_therm_ic_ctor(therm);
	nouveau_therm_fan_ctor(therm);

	nouveau_therm_fan_mode(therm, NOUVEAU_THERM_CTRL_NONE);
	nouveau_therm_sensor_preinit(therm);
	return 0;
}