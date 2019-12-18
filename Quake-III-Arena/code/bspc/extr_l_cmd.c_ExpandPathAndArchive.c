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
 char* ExpandPath (char*) ; 
 int /*<<< orphan*/  QCopyFile (char*,char*) ; 
 scalar_t__ archive ; 
 char* archivedir ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 

char *ExpandPathAndArchive (char *path)
{
	char	*expanded;
	char	archivename[1024];

	expanded = ExpandPath (path);

	if (archive)
	{
		sprintf (archivename, "%s/%s", archivedir, path);
		QCopyFile (expanded, archivename);
	}
	return expanded;
}