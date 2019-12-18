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
 scalar_t__ access (char*,int) ; 
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
		ld[8] = concat("-L", &arg[8]);
	} else if (strcmp(arg, "-g4") == 0
	&& access("/u/drh/lib/alpha/rcc", 4) == 0
	&& access("/u/drh/book/cdb/alpha/osf/cdbld", 4) == 0) {
		com[0] = "/u/drh/lib/alpha/rcc";
		com[5] = "-g4";
		ld[0] = "/u/drh/book/cdb/alpha/osf/cdbld";
		ld[1] = "-o";
		ld[2] = "$3";
		ld[3] = "$1";
		ld[4] = "$2";
		ld[5] = 0;
	} else if (strcmp(arg, "-g") == 0)
		return 1;
	else if (strcmp(arg, "-b") == 0)
		;
	else
		return 0;
	return 1;
}