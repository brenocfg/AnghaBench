#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;
struct TYPE_4__ {int /*<<< orphan*/  dependedJobList; int /*<<< orphan*/  jobId; } ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ Job ;

/* Variables and functions */
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ linitial (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_concat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_delete_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_make1 (TYPE_1__*) ; 
 scalar_t__ palloc0 (int) ; 

__attribute__((used)) static List *
JobIdList(Job *job)
{
	List *jobIdList = NIL;
	List *jobQueue = NIL;

	/*
	 * We walk over the job tree using breadth-first search. For this, we first
	 * queue the root node, and then start traversing our search space.
	 */
	jobQueue = list_make1(job);
	while (jobQueue != NIL)
	{
		uint64 *jobIdPointer = (uint64 *) palloc0(sizeof(uint64));
		List *jobChildrenList = NIL;

		Job *currJob = (Job *) linitial(jobQueue);
		jobQueue = list_delete_first(jobQueue);

		(*jobIdPointer) = currJob->jobId;
		jobIdList = lappend(jobIdList, jobIdPointer);

		/* prevent dependedJobList being modified on list_concat() call */
		jobChildrenList = list_copy(currJob->dependedJobList);
		if (jobChildrenList != NIL)
		{
			jobQueue = list_concat(jobQueue, jobChildrenList);
		}
	}

	return jobIdList;
}