#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int visible; } ;
typedef  TYPE_1__* Portal ;
typedef  int /*<<< orphan*/  PlannedStmt ;
typedef  int /*<<< orphan*/  ParamListInfo ;
typedef  int /*<<< orphan*/  DestReceiver ;

/* Variables and functions */
 TYPE_1__* CreateNewPortal () ; 
 long FETCH_ALL ; 
 int /*<<< orphan*/  GetActiveSnapshot () ; 
 int /*<<< orphan*/  PortalDefineQuery (TYPE_1__*,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PortalDrop (TYPE_1__*,int) ; 
 int /*<<< orphan*/  PortalRun (TYPE_1__*,long,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PortalStart (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_make1 (int /*<<< orphan*/ *) ; 

void
ExecutePlanIntoDestReceiver(PlannedStmt *queryPlan, ParamListInfo params,
							DestReceiver *dest)
{
	Portal portal = NULL;
	int eflags = 0;
	long count = FETCH_ALL;

	/* create a new portal for executing the query */
	portal = CreateNewPortal();

	/* don't display the portal in pg_cursors, it is for internal use only */
	portal->visible = false;

	PortalDefineQuery(portal,
					  NULL,
					  "",
					  "SELECT",
					  list_make1(queryPlan),
					  NULL);

	PortalStart(portal, params, eflags, GetActiveSnapshot());
	PortalRun(portal, count, false, true, dest, dest, NULL);
	PortalDrop(portal, false);
}