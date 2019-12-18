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
 char* DIVA_BUILD ; 
 char* DRIVERLNAME ; 
 char* DRIVERRELEASE_DIVAS ; 
 char* diva_xdi_common_code_build ; 
 char* getrev (char*) ; 
 int /*<<< orphan*/  main_revision ; 
 int major ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,char*,char*,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

void divas_get_version(char *p)
{
	char tmprev[32];

	strcpy(tmprev, main_revision);
	sprintf(p, "%s: %s(%s) %s(%s) major=%d\n", DRIVERLNAME, DRIVERRELEASE_DIVAS,
		getrev(tmprev), diva_xdi_common_code_build, DIVA_BUILD, major);
}