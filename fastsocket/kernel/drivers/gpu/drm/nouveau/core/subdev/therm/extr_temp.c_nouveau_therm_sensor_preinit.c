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
struct nouveau_therm {scalar_t__ (* temp_get ) (struct nouveau_therm*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  nv_info (struct nouveau_therm*,char*,char const*) ; 
 scalar_t__ stub1 (struct nouveau_therm*) ; 

void
nouveau_therm_sensor_preinit(struct nouveau_therm *therm)
{
	const char *sensor_avail = "yes";

	if (therm->temp_get(therm) < 0)
		sensor_avail = "no";

	nv_info(therm, "internal sensor: %s\n", sensor_avail);
}