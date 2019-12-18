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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char** dirs ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 

FILE *openfile(char *name) {
	int i;
	FILE *fp;

	if (*name != '/')	
		for (i = 0; dirs[i]; i++) {
			char buf[200];
			sprintf(buf, "%s/%s", dirs[i], name);
			if (fp = fopen(buf, "r"))
				return fp;
		}
	return fopen(name, "r");
}