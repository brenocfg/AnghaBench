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
struct stat {int /*<<< orphan*/  st_mode; } ;
struct dirent {int /*<<< orphan*/  d_name; } ;

/* Variables and functions */
 int FALSE ; 
 int FILENAME_MAX ; 
 int S_ISDIR (int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/  Util_catpath (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dir_path ; 
 int /*<<< orphan*/ * dp ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int BasicUIReadDir(char *filename, int *isdir)
{
	struct dirent *entry;
	char fullfilename[FILENAME_MAX];
	struct stat st;
	entry = readdir(dp);
	if (entry == NULL) {
		closedir(dp);
		dp = NULL;
		return FALSE;
	}
	strcpy(filename, entry->d_name);
	Util_catpath(fullfilename, dir_path, entry->d_name);
	stat(fullfilename, &st);
	*isdir = S_ISDIR(st.st_mode);
	return TRUE;
}