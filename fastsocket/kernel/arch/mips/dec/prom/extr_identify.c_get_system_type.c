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
 int STR_BUF_LEN ; 
 char** dec_system_strings ; 
 size_t mips_machtype ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

const char *get_system_type(void)
{
#define STR_BUF_LEN	64
	static char system[STR_BUF_LEN];
	static int called = 0;

	if (called == 0) {
		called = 1;
		snprintf(system, STR_BUF_LEN, "Digital %s",
			 dec_system_strings[mips_machtype]);
	}

	return system;
}