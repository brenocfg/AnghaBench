#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  taskId; int /*<<< orphan*/  jobId; } ;
typedef  TYPE_1__ Task ;
typedef  int /*<<< orphan*/ * StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_ASSIGNMENT_QUERY ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * makeStringInfo () ; 
 char* quote_literal_cstr (char*) ; 

__attribute__((used)) static StringInfo
TaskAssignmentQuery(Task *task, char *queryString)
{
	StringInfo taskAssignmentQuery = NULL;

	/* quote the original query as a string literal */
	char *escapedQueryString = quote_literal_cstr(queryString);

	taskAssignmentQuery = makeStringInfo();
	appendStringInfo(taskAssignmentQuery, TASK_ASSIGNMENT_QUERY,
					 task->jobId, task->taskId, escapedQueryString);

	return taskAssignmentQuery;
}