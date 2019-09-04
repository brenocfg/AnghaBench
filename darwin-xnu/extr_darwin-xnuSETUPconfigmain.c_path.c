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
 char* build_directory ; 
 char* malloc (unsigned int) ; 
 char* object_directory ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

char *
path(const char *file)
{
	char *cp;

	cp = malloc((unsigned)(strlen(build_directory)+
			       strlen(file)+
			       strlen(object_directory)+
			       3));
	(void) sprintf(cp, "%s/%s/%s", object_directory, build_directory, file);
	return (cp);
}