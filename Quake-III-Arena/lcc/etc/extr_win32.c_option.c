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
 char* replace (char*,char,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

int option(char *arg) {
	if (strncmp(arg, "-lccdir=", 8) == 0) {
		arg = replace(arg + 8, '/', '\\');
		if (arg[strlen(arg)-1] == '\\')
			arg[strlen(arg)-1] = '\0';
		cpp[0] = concat(arg, "\\cpp.exe");
		include[0] = concat("-I", concat(arg, "\\include"));
		com[0] = concat(arg, "\\rcc.exe");
		ld[8] = concat(arg, "\\liblcc.lib");
	} else if (strcmp(arg, "-b") == 0)
		;
	else if (strncmp(arg, "-ld=", 4) == 0)
		ld[0] = &arg[4];
	else
		return 0;
	return 1;
}