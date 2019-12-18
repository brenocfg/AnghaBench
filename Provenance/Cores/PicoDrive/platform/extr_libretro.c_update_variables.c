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
struct retro_variable {char* key; int /*<<< orphan*/ * value; } ;

/* Variables and functions */
 int /*<<< orphan*/  POPT_DIS_SPRITE_LIM ; 
 int /*<<< orphan*/  POPT_EN_DRC ; 
 int /*<<< orphan*/  POPT_EN_MCD_RAMCART ; 
 int /*<<< orphan*/  PicoOpt ; 
 int /*<<< orphan*/  PicoSetInputDevice (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RETRO_ENVIRONMENT_GET_VARIABLE ; 
 scalar_t__ environ_cb (int /*<<< orphan*/ ,struct retro_variable*) ; 
 int /*<<< orphan*/  input_name_to_val (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void update_variables(void)
{
	struct retro_variable var;

	var.value = NULL;
	var.key = "picodrive_input1";
	if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
		PicoSetInputDevice(0, input_name_to_val(var.value));

	var.value = NULL;
	var.key = "picodrive_input2";
	if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
		PicoSetInputDevice(1, input_name_to_val(var.value));

	var.value = NULL;
	var.key = "picodrive_sprlim";
	if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value) {
		if (strcmp(var.value, "enabled") == 0)
			PicoOpt |= POPT_DIS_SPRITE_LIM;
		else
			PicoOpt &= ~POPT_DIS_SPRITE_LIM;
	}

	var.value = NULL;
	var.key = "picodrive_ramcart";
	if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value) {
		if (strcmp(var.value, "enabled") == 0)
			PicoOpt |= POPT_EN_MCD_RAMCART;
		else
			PicoOpt &= ~POPT_EN_MCD_RAMCART;
	}

#ifdef DRC_SH2
	var.value = NULL;
	var.key = "picodrive_drc";
	if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value) {
		if (strcmp(var.value, "enabled") == 0)
			PicoOpt |= POPT_EN_DRC;
		else
			PicoOpt &= ~POPT_EN_DRC;
	}
#endif
}