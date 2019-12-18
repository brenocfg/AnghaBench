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
typedef  scalar_t__ File ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ PathNameOpenFilePerm (char*,int,int) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 int stat (char const*,struct stat*) ; 

File
FileOpenForTransmit(const char *filename, int fileFlags, int fileMode)
{
	File fileDesc = -1;
	int fileStated = -1;
	struct stat fileStat;

	fileStated = stat(filename, &fileStat);
	if (fileStated >= 0)
	{
		if (S_ISDIR(fileStat.st_mode))
		{
			ereport(ERROR, (errcode(ERRCODE_WRONG_OBJECT_TYPE),
							errmsg("\"%s\" is a directory", filename)));
		}
	}

	fileDesc = PathNameOpenFilePerm((char *) filename, fileFlags, fileMode);
	if (fileDesc < 0)
	{
		ereport(ERROR, (errcode_for_file_access(),
						errmsg("could not open file \"%s\": %m", filename)));
	}

	return fileDesc;
}