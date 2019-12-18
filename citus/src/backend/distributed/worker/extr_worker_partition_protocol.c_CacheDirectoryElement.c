#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  PG_JOB_CACHE_DIR ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* makeStringInfo () ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 
 char* strstr (char const*,int /*<<< orphan*/ ) ; 

bool
CacheDirectoryElement(const char *filename)
{
	bool directoryElement = false;
	char *directoryPathFound = NULL;

	StringInfo directoryPath = makeStringInfo();
	appendStringInfo(directoryPath, "base/%s/", PG_JOB_CACHE_DIR);

	directoryPathFound = strstr(filename, directoryPath->data);

	/*
	 * If directoryPath occurs at the beginning of the filename, then the
	 * pointers should now be equal.
	 */
	if (directoryPathFound == filename)
	{
		directoryElement = true;
	}

	pfree(directoryPath);

	return directoryElement;
}