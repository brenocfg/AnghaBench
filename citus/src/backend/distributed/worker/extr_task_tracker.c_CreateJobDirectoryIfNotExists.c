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
typedef  int /*<<< orphan*/  uint64 ;
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  CitusCreateDirectory (int /*<<< orphan*/ ) ; 
 int DirectoryExists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeStringInfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JobDirectoryName (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
CreateJobDirectoryIfNotExists(uint64 jobId)
{
	StringInfo jobDirectoryName = JobDirectoryName(jobId);

	bool jobDirectoryExists = DirectoryExists(jobDirectoryName);
	if (!jobDirectoryExists)
	{
		CitusCreateDirectory(jobDirectoryName);
	}

	FreeStringInfo(jobDirectoryName);
}