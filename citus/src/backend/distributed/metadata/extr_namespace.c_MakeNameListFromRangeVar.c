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
struct TYPE_3__ {int /*<<< orphan*/ * relname; int /*<<< orphan*/ * schemaname; int /*<<< orphan*/ * catalogname; } ;
typedef  TYPE_1__ RangeVar ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_make1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_make2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_make3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeString (int /*<<< orphan*/ *) ; 

List *
MakeNameListFromRangeVar(const RangeVar *rel)
{
	if (rel->catalogname != NULL)
	{
		Assert(rel->schemaname != NULL);
		Assert(rel->relname != NULL);
		return list_make3(makeString(rel->catalogname),
						  makeString(rel->schemaname),
						  makeString(rel->relname));
	}
	else if (rel->schemaname != NULL)
	{
		Assert(rel->relname != NULL);
		return list_make2(makeString(rel->schemaname),
						  makeString(rel->relname));
	}
	else
	{
		Assert(rel->relname != NULL);
		return list_make1(makeString(rel->relname));
	}
}