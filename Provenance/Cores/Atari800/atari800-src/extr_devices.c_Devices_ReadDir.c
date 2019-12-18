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
struct tm {int tm_hour; int tm_mon; int tm_mday; int tm_year; int tm_min; } ;
struct stat {int st_mode; int /*<<< orphan*/  st_mtime; scalar_t__ st_size; } ;
struct dirent {char* d_name; } ;

/* Variables and functions */
 int FALSE ; 
 int FILENAME_MAX ; 
 int S_ISDIR (int) ; 
 int S_IWRITE ; 
 int TRUE ; 
 int /*<<< orphan*/  Util_catpath (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dir_path ; 
 int /*<<< orphan*/ * dp ; 
 char* filename_pattern ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 scalar_t__ match (char*,char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,int,int,char) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static int Devices_ReadDir(char *fullpath, char *filename, int *isdir,
                          int *readonly, int *size, char *timetext)
{
	struct dirent *entry;
	char temppath[FILENAME_MAX];
#ifdef HAVE_STAT
	struct stat status;
#endif
	for (;;) {
		entry = readdir(dp);
		if (entry == NULL) {
			closedir(dp);
			dp = NULL;
			return FALSE;
		}
		if (entry->d_name[0] == '.') {
			/* don't match Unix hidden files unless specifically requested */
			if (filename_pattern[0] != '.')
				continue;
			/* never match "." */
			if (entry->d_name[1] == '\0')
				continue;
			/* never match ".." */
			if (entry->d_name[1] == '.' && entry->d_name[2] == '\0')
				continue;
		}
		if (match(filename_pattern, entry->d_name))
			break;
	}
	if (filename != NULL)
		strcpy(filename, entry->d_name);
	Util_catpath(temppath, dir_path, entry->d_name);
	if (fullpath != NULL)
		strcpy(fullpath, temppath);
#ifdef HAVE_STAT
	if (stat(temppath, &status) == 0) {
		if (isdir != NULL)
			*isdir = S_ISDIR(status.st_mode);
		if (readonly != NULL)
			*readonly = (status.st_mode & S_IWRITE) ? FALSE : TRUE;
		if (size != NULL)
			*size = (int) status.st_size;
		if (timetext != NULL) {
#ifdef HAVE_LOCALTIME
			struct tm *ft;
			int hour;
			char ampm = 'a';
			ft = localtime(&status.st_mtime);
			hour = ft->tm_hour;
			if (hour >= 12) {
				hour -= 12;
				ampm = 'p';
			}
			if (hour == 0)
				hour = 12;
			sprintf(timetext, "%2d-%02d-%02d %2d:%02d%c",
				ft->tm_mon + 1, ft->tm_mday, ft->tm_year % 100,
				hour, ft->tm_min, ampm);
#else
			strcpy(timetext, " 1-01-01 12:00p");
#endif /* HAVE_LOCALTIME */
		}
	}
	else
#endif /* HAVE_STAT */
	{
		if (isdir != NULL)
			*isdir = FALSE;
		if (readonly != NULL)
			*readonly = FALSE;
		if (size != NULL)
			*size = 0;
		if (timetext != NULL)
			strcpy(timetext, " 1-01-01 12:00p");
	}
	return TRUE;
}