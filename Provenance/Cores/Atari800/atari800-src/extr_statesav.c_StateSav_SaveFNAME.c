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
typedef  scalar_t__ UWORD ;
typedef  int /*<<< orphan*/  UBYTE ;

/* Variables and functions */
 int FILENAME_MAX ; 
 int /*<<< orphan*/  StateSav_SaveUBYTE (int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  StateSav_SaveUWORD (scalar_t__*,int) ; 
 int /*<<< orphan*/ * getcwd (char*,int) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,scalar_t__) ; 

void StateSav_SaveFNAME(const char *filename)
{
	UWORD namelen;
#ifdef HAVE_GETCWD
	char dirname[FILENAME_MAX]="";

	/* Check to see if file is in application tree, if so, just save as
	   relative path....*/
	if (getcwd(dirname, FILENAME_MAX) != NULL) {
		if (strncmp(filename, dirname, strlen(dirname)) == 0)
			/* XXX: check if '/' or '\\' follows dirname in filename? */
			filename += strlen(dirname) + 1;
	}
#endif

	namelen = strlen(filename);
	/* Save the length of the filename, followed by the filename */
	StateSav_SaveUWORD(&namelen, 1);
	StateSav_SaveUBYTE((const UBYTE *) filename, namelen);
}