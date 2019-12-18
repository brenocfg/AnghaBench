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
struct TYPE_4__ {int /*<<< orphan*/  rels; } ;
typedef  TYPE_1__ VacuumStmt ;
struct TYPE_5__ {int /*<<< orphan*/ * va_cols; } ;
typedef  TYPE_2__ VacuumRelation ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 scalar_t__ list_nth (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static List *
VacuumColumnList(VacuumStmt *vacuumStmt, int relationIndex)
{
	VacuumRelation *vacuumRelation = (VacuumRelation *) list_nth(vacuumStmt->rels,
																 relationIndex);

	return vacuumRelation->va_cols;
}