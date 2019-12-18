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
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  CitusCreateDirectory (int /*<<< orphan*/ ) ; 
 int DirectoryExists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JobDirectoryName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockJobResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TaskDirectoryName (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockJobResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

StringInfo
InitTaskDirectory(uint64 jobId, uint32 taskId)
{
	bool jobDirectoryExists = false;
	bool taskDirectoryExists = false;

	/*
	 * If the task tracker assigned this task (regular case), the tracker should
	 * have already created the job directory.
	 */
	StringInfo jobDirectoryName = JobDirectoryName(jobId);
	StringInfo taskDirectoryName = TaskDirectoryName(jobId, taskId);

	LockJobResource(jobId, AccessExclusiveLock);

	jobDirectoryExists = DirectoryExists(jobDirectoryName);
	if (!jobDirectoryExists)
	{
		CitusCreateDirectory(jobDirectoryName);
	}

	taskDirectoryExists = DirectoryExists(taskDirectoryName);
	if (!taskDirectoryExists)
	{
		CitusCreateDirectory(taskDirectoryName);
	}

	UnlockJobResource(jobId, AccessExclusiveLock);

	return taskDirectoryName;
}