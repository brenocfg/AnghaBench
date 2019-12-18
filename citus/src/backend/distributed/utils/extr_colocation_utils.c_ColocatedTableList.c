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
typedef  scalar_t__ uint32 ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/ * ColocationGroupTableList (scalar_t__) ; 
 scalar_t__ INVALID_COLOCATION_ID ; 
 int /*<<< orphan*/ * NIL ; 
 scalar_t__ TableColocationId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lappend_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

List *
ColocatedTableList(Oid distributedTableId)
{
	uint32 tableColocationId = TableColocationId(distributedTableId);
	List *colocatedTableList = NIL;

	/*
	 * If distribution type of the table is not hash, the table is only co-located
	 * with itself.
	 */
	if (tableColocationId == INVALID_COLOCATION_ID)
	{
		colocatedTableList = lappend_oid(colocatedTableList, distributedTableId);
		return colocatedTableList;
	}

	colocatedTableList = ColocationGroupTableList(tableColocationId);

	return colocatedTableList;
}