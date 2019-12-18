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
 char PATHSEPERATOR_CHAR ; 
 int strlen (char*) ; 

void AppendPathSeperator(char *path, int length)
{
	int pathlen = strlen(path);

	if (strlen(path) && length-pathlen > 1 && path[pathlen-1] != '/' && path[pathlen-1] != '\\')
	{
		path[pathlen] = PATHSEPERATOR_CHAR;
		path[pathlen+1] = '\0';
	} //end if
}