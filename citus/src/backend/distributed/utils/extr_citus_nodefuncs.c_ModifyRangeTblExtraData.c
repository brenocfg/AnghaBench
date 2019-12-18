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
typedef  int /*<<< orphan*/  RangeTblEntry ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  CitusRTEKind ;

/* Variables and functions */
 int /*<<< orphan*/  ExtractRangeTblExtraData (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**,char**,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  SetRangeTblExtraData (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 

void
ModifyRangeTblExtraData(RangeTblEntry *rte, CitusRTEKind rteKind,
						char *fragmentSchemaName, char *fragmentTableName,
						List *tableIdList)
{
	/* load existing values for the arguments not specifying a new value */
	ExtractRangeTblExtraData(rte, NULL,
							 fragmentSchemaName == NULL ? &fragmentSchemaName : NULL,
							 fragmentTableName == NULL ? &fragmentTableName : NULL,
							 tableIdList == NIL ? &tableIdList : NULL);

	SetRangeTblExtraData(rte, rteKind,
						 fragmentSchemaName, fragmentTableName,
						 tableIdList);
}