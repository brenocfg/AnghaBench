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
typedef  int /*<<< orphan*/  uint64 ;
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* StringInfo ;

/* Variables and functions */
 TYPE_1__* JobDirectoryName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN_TASK_FILENAME_WIDTH ; 
 int /*<<< orphan*/  TASK_FILE_PREFIX ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* makeStringInfo () ; 

StringInfo
TaskDirectoryName(uint64 jobId, uint32 taskId)
{
	StringInfo jobDirectoryName = JobDirectoryName(jobId);

	StringInfo taskDirectoryName = makeStringInfo();
	appendStringInfo(taskDirectoryName, "%s/%s%0*u",
					 jobDirectoryName->data,
					 TASK_FILE_PREFIX, MIN_TASK_FILENAME_WIDTH, taskId);

	return taskDirectoryName;
}