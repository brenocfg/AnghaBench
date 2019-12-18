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
struct TYPE_3__ {int /*<<< orphan*/  arg; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ DefElem ;

/* Variables and functions */
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ intVal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
AppendDefElemLeakproof(StringInfo buf, DefElem *def)
{
	if (intVal(def->arg) == 0)
	{
		appendStringInfo(buf, " NOT");
	}
	appendStringInfo(buf, " LEAKPROOF");
}