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
typedef  int /*<<< orphan*/  Job ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_UINT64_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deferredPruning ; 
 int /*<<< orphan*/  dependedJobList ; 
 int /*<<< orphan*/  jobId ; 
 int /*<<< orphan*/  jobQuery ; 
 int /*<<< orphan*/  partitionKeyValue ; 
 int /*<<< orphan*/  requiresMasterEvaluation ; 
 int /*<<< orphan*/  subqueryPushdown ; 
 int /*<<< orphan*/  taskList ; 

__attribute__((used)) static void
OutJobFields(StringInfo str, const Job *node)
{
	WRITE_UINT64_FIELD(jobId);
	WRITE_NODE_FIELD(jobQuery);
	WRITE_NODE_FIELD(taskList);
	WRITE_NODE_FIELD(dependedJobList);
	WRITE_BOOL_FIELD(subqueryPushdown);
	WRITE_BOOL_FIELD(requiresMasterEvaluation);
	WRITE_BOOL_FIELD(deferredPruning);
	WRITE_NODE_FIELD(partitionKeyValue);
}