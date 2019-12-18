#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * columnList; } ;
typedef  TYPE_1__ MultiProject ;
typedef  int /*<<< orphan*/  MultiNode ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * FindNodesOfType (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  T_MultiProject ; 
 int /*<<< orphan*/ * TargetEntryList (int /*<<< orphan*/ *) ; 
 scalar_t__ linitial (int /*<<< orphan*/ *) ; 
 scalar_t__ list_length (int /*<<< orphan*/ *) ; 

__attribute__((used)) static List *
QueryTargetList(MultiNode *multiNode)
{
	MultiProject *topProjectNode = NULL;
	List *columnList = NIL;
	List *queryTargetList = NIL;

	List *projectNodeList = FindNodesOfType(multiNode, T_MultiProject);
	Assert(list_length(projectNodeList) > 0);

	topProjectNode = (MultiProject *) linitial(projectNodeList);
	columnList = topProjectNode->columnList;
	queryTargetList = TargetEntryList(columnList);

	Assert(queryTargetList != NIL);
	return queryTargetList;
}