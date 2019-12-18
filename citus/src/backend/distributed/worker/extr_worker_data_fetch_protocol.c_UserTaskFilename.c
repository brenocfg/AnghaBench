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
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  TaskFilename (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

StringInfo
UserTaskFilename(StringInfo directoryName, uint32 taskId)
{
	StringInfo taskFilename = TaskFilename(directoryName, taskId);

	appendStringInfo(taskFilename, ".%u", GetUserId());

	return taskFilename;
}