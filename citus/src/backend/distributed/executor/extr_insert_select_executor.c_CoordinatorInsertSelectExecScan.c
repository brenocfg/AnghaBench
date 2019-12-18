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
typedef  int /*<<< orphan*/  TupleTableSlot ;
typedef  int /*<<< orphan*/  CustomScanState ;

/* Variables and functions */
 int /*<<< orphan*/ * CoordinatorInsertSelectExecScanInternal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PG_CATCH () ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_RE_THROW () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 int /*<<< orphan*/  insertSelectExecutorLevel ; 

TupleTableSlot *
CoordinatorInsertSelectExecScan(CustomScanState *node)
{
	TupleTableSlot *result = NULL;
	insertSelectExecutorLevel++;

	PG_TRY();
	{
		result = CoordinatorInsertSelectExecScanInternal(node);
	}
	PG_CATCH();
	{
		insertSelectExecutorLevel--;
		PG_RE_THROW();
	}
	PG_END_TRY();

	insertSelectExecutorLevel--;
	return result;
}