#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  rtable; TYPE_1__* jointree; } ;
struct TYPE_8__ {int /*<<< orphan*/  rtindex; } ;
struct TYPE_7__ {int /*<<< orphan*/ * fromlist; } ;
typedef  TYPE_2__ RangeTblRef ;
typedef  int /*<<< orphan*/  RangeTblEntry ;
typedef  TYPE_3__ Query ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InsertSelectIntoDistributedTable (TYPE_3__*) ; 
 TYPE_2__* linitial (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rt_fetch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

RangeTblEntry *
ExtractSelectRangeTableEntry(Query *query)
{
	List *fromList = NULL;
	RangeTblRef *reference = NULL;
	RangeTblEntry *subqueryRte = NULL;

	Assert(InsertSelectIntoDistributedTable(query));

	/*
	 * Since we already asserted InsertSelectIntoDistributedTable() it is safe to access
	 * both lists
	 */
	fromList = query->jointree->fromlist;
	reference = linitial(fromList);
	subqueryRte = rt_fetch(reference->rtindex, query->rtable);

	return subqueryRte;
}