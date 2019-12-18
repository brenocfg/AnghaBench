#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  defname; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ DefElem ;

/* Variables and functions */
 int /*<<< orphan*/  AppendDefElemCost (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  AppendDefElemLeakproof (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  AppendDefElemParallel (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  AppendDefElemRows (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  AppendDefElemSecurity (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  AppendDefElemSet (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  AppendDefElemStrict (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  AppendDefElemVolatility (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
AppendDefElem(StringInfo buf, DefElem *def)
{
	if (strcmp(def->defname, "strict") == 0)
	{
		AppendDefElemStrict(buf, def);
	}
	else if (strcmp(def->defname, "volatility") == 0)
	{
		AppendDefElemVolatility(buf, def);
	}
	else if (strcmp(def->defname, "leakproof") == 0)
	{
		AppendDefElemLeakproof(buf, def);
	}
	else if (strcmp(def->defname, "security") == 0)
	{
		AppendDefElemSecurity(buf, def);
	}
	else if (strcmp(def->defname, "parallel") == 0)
	{
		AppendDefElemParallel(buf, def);
	}
	else if (strcmp(def->defname, "cost") == 0)
	{
		AppendDefElemCost(buf, def);
	}
	else if (strcmp(def->defname, "rows") == 0)
	{
		AppendDefElemRows(buf, def);
	}
	else if (strcmp(def->defname, "set") == 0)
	{
		AppendDefElemSet(buf, def);
	}
}