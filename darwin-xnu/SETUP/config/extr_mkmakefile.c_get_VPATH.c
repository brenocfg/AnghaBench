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
 char* getenv (char*) ; 
 char* malloc (unsigned int) ; 
 char* strcat (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

const char *
get_VPATH(void)
{
    static char *vpath = NULL;

    if ((vpath == NULL) &&
	((vpath = getenv("VPATH")) != NULL) &&
	(*vpath != ':')) {
	char *buf = malloc((unsigned)(strlen(vpath) + 2));

	vpath = strcat(strcpy(buf, ":"), vpath);
    }

    return vpath ? vpath : "";
}