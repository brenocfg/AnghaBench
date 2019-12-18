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

/* Variables and functions */
 int BLERR_NOERROR ; 
 char* LibVarGetString (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

int Export_BotLibVarGet(char *var_name, char *value, int size)
{
	char *varvalue;

	varvalue = LibVarGetString(var_name);
	strncpy(value, varvalue, size-1);
	value[size-1] = '\0';
	return BLERR_NOERROR;
}