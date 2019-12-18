#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
struct dirent {char* d_name; } ;
struct TYPE_6__ {char const* data; } ;
typedef  TYPE_1__* StringInfo ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/ * AllocateDir (char const*) ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FileIsLink (char const*,struct stat) ; 
 int /*<<< orphan*/  FreeDir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeStringInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  MAXPGPATH ; 
 struct dirent* ReadDir (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,char const*,char const*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 scalar_t__ errno ; 
 TYPE_1__* makeStringInfo () ; 
 int rmdir (char*) ; 
 int stat (char const*,struct stat*) ; 
 scalar_t__ strncmp (char const*,char*,int /*<<< orphan*/ ) ; 
 int unlink (char*) ; 

void
CitusRemoveDirectory(StringInfo filename)
{
	struct stat fileStat;
	int removed = 0;

	int fileStated = stat(filename->data, &fileStat);
	if (fileStated < 0)
	{
		if (errno == ENOENT)
		{
			return;  /* if file does not exist, return */
		}
		else
		{
			ereport(ERROR, (errcode_for_file_access(),
							errmsg("could not stat file \"%s\": %m", filename->data)));
		}
	}

	/*
	 * If this is a directory, iterate over all its contents and for each
	 * content, recurse into this function. Also, make sure that we do not
	 * recurse into symbolic links.
	 */
	if (S_ISDIR(fileStat.st_mode) && !FileIsLink(filename->data, fileStat))
	{
		const char *directoryName = filename->data;
		struct dirent *directoryEntry = NULL;

		DIR *directory = AllocateDir(directoryName);
		if (directory == NULL)
		{
			ereport(ERROR, (errcode_for_file_access(),
							errmsg("could not open directory \"%s\": %m",
								   directoryName)));
		}

		directoryEntry = ReadDir(directory, directoryName);
		for (; directoryEntry != NULL; directoryEntry = ReadDir(directory, directoryName))
		{
			const char *baseFilename = directoryEntry->d_name;
			StringInfo fullFilename = NULL;

			/* if system file, skip it */
			if (strncmp(baseFilename, ".", MAXPGPATH) == 0 ||
				strncmp(baseFilename, "..", MAXPGPATH) == 0)
			{
				continue;
			}

			fullFilename = makeStringInfo();
			appendStringInfo(fullFilename, "%s/%s", directoryName, baseFilename);

			CitusRemoveDirectory(fullFilename);

			FreeStringInfo(fullFilename);
		}

		FreeDir(directory);
	}

	/* we now have an empty directory or a regular file, remove it */
	if (S_ISDIR(fileStat.st_mode))
	{
		removed = rmdir(filename->data);
	}
	else
	{
		removed = unlink(filename->data);
	}

	if (removed != 0)
	{
		ereport(ERROR, (errcode_for_file_access(),
						errmsg("could not remove file \"%s\": %m", filename->data)));
	}
}