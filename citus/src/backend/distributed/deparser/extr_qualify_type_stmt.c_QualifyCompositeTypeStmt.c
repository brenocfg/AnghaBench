#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * schemaname; } ;
struct TYPE_4__ {TYPE_2__* typevar; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ CompositeTypeStmt ;

/* Variables and functions */
 int /*<<< orphan*/  RangeVarGetCreationNamespace (TYPE_2__*) ; 
 int /*<<< orphan*/ * get_namespace_name (int /*<<< orphan*/ ) ; 

void
QualifyCompositeTypeStmt(CompositeTypeStmt *stmt)
{
	if (stmt->typevar->schemaname == NULL)
	{
		Oid creationSchema = RangeVarGetCreationNamespace(stmt->typevar);
		stmt->typevar->schemaname = get_namespace_name(creationSchema);
	}
}