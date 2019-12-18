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
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  CitusCreateDirectory (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CitusRemoveDirectory (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeStringInfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_JOB_CACHE_DIR ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeStringInfo () ; 

__attribute__((used)) static void
TrackerCleanupJobDirectories(void)
{
	/* use the default tablespace in {datadir}/base */
	StringInfo jobCacheDirectory = makeStringInfo();
	appendStringInfo(jobCacheDirectory, "base/%s", PG_JOB_CACHE_DIR);

	CitusRemoveDirectory(jobCacheDirectory);
	CitusCreateDirectory(jobCacheDirectory);

	FreeStringInfo(jobCacheDirectory);
}