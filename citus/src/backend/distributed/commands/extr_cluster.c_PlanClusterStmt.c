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
struct TYPE_3__ {int /*<<< orphan*/ * relation; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ ClusterStmt ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  InvalidOid ; 
 int IsDistributedTable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RangeVarGetRelid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

List *
PlanClusterStmt(ClusterStmt *clusterStmt, const char *clusterCommand)
{
	bool showPropagationWarning = false;

	/* CLUSTER all */
	if (clusterStmt->relation == NULL)
	{
		showPropagationWarning = true;
	}
	else
	{
		Oid relationId = InvalidOid;
		bool missingOK = false;

		relationId = RangeVarGetRelid(clusterStmt->relation, AccessShareLock,
									  missingOK);

		if (OidIsValid(relationId))
		{
			showPropagationWarning = IsDistributedTable(relationId);
		}
	}

	if (showPropagationWarning)
	{
		ereport(WARNING, (errmsg("not propagating CLUSTER command to worker nodes")));
	}

	return NIL;
}