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
 char** com ; 
 char* concat (char*,char*) ; 
 char** cpp ; 
 char** include ; 
 char** ld ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

int option(char *arg) {
	if (strncmp(arg, "-lccdir=", 8) == 0) {
		cpp[0] = concat(&arg[8], "/cpp");
		include[0] = concat("-I", concat(&arg[8], "/include"));
		com[0] = concat(&arg[8], "/rcc");
		ld[17] = concat("-L", &arg[8]);
	} else if (strcmp(arg, "-g") == 0)
		;
	else if (strcmp(arg, "-p") == 0)
		ld[12] = "/usr/lib/mcrt1.o";
	else if (strcmp(arg, "-b") == 0)
		;
	else
		return 0;
	return 1;
}