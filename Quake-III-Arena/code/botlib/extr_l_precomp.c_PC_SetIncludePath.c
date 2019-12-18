#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* includepath; } ;
typedef  TYPE_1__ source_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  PATHSEPERATOR_STR ; 
 int /*<<< orphan*/  strcat (char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int /*<<< orphan*/ ) ; 

void PC_SetIncludePath(source_t *source, char *path)
{
	strncpy(source->includepath, path, MAX_PATH);
	//add trailing path seperator
	if (source->includepath[strlen(source->includepath)-1] != '\\' &&
		source->includepath[strlen(source->includepath)-1] != '/')
	{
		strcat(source->includepath, PATHSEPERATOR_STR);
	} //end if
}