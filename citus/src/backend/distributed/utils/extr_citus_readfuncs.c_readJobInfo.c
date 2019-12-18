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
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  Job ;

/* Variables and functions */
 int /*<<< orphan*/  CitusSetTag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ_TEMP_LOCALS () ; 
 int /*<<< orphan*/  READ_UINT64_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_Job ; 
 int /*<<< orphan*/  deferredPruning ; 
 int /*<<< orphan*/  dependedJobList ; 
 int /*<<< orphan*/  jobId ; 
 int /*<<< orphan*/  jobQuery ; 
 int /*<<< orphan*/  partitionKeyValue ; 
 int /*<<< orphan*/  requiresMasterEvaluation ; 
 int /*<<< orphan*/  subqueryPushdown ; 
 int /*<<< orphan*/  taskList ; 

__attribute__((used)) static void
readJobInfo(Job *local_node)
{
	READ_TEMP_LOCALS();

	CitusSetTag((Node *) local_node, T_Job);

	READ_UINT64_FIELD(jobId);
	READ_NODE_FIELD(jobQuery);
	READ_NODE_FIELD(taskList);
	READ_NODE_FIELD(dependedJobList);
	READ_BOOL_FIELD(subqueryPushdown);
	READ_BOOL_FIELD(requiresMasterEvaluation);
	READ_BOOL_FIELD(deferredPruning);
	READ_NODE_FIELD(partitionKeyValue);
}