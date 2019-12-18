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
typedef  int /*<<< orphan*/  Job ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COPY_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deferredPruning ; 
 int /*<<< orphan*/  dependedJobList ; 
 int /*<<< orphan*/  jobId ; 
 int /*<<< orphan*/  jobQuery ; 
 int /*<<< orphan*/  partitionKeyValue ; 
 int /*<<< orphan*/  requiresMasterEvaluation ; 
 int /*<<< orphan*/  subqueryPushdown ; 
 int /*<<< orphan*/  taskList ; 

__attribute__((used)) static void
copyJobInfo(Job *newnode, Job *from)
{
	COPY_SCALAR_FIELD(jobId);
	COPY_NODE_FIELD(jobQuery);
	COPY_NODE_FIELD(taskList);
	COPY_NODE_FIELD(dependedJobList);
	COPY_SCALAR_FIELD(subqueryPushdown);
	COPY_SCALAR_FIELD(requiresMasterEvaluation);
	COPY_SCALAR_FIELD(deferredPruning);
	COPY_NODE_FIELD(partitionKeyValue);
}