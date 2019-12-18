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
 int PROC_INTERFACE_VERSION ; 
 char* TOSHIBA_ACPI_VERSION ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static char *read_version(char *p)
{
	p += sprintf(p, "driver:                  %s\n", TOSHIBA_ACPI_VERSION);
	p += sprintf(p, "proc_interface:          %d\n",
		     PROC_INTERFACE_VERSION);
	return p;
}