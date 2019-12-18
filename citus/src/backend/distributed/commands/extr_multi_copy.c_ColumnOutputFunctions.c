#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
typedef  TYPE_1__* TupleDesc ;
struct TYPE_4__ {int /*<<< orphan*/  natts; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  FmgrInfo ;

/* Variables and functions */
 int /*<<< orphan*/ * TypeArrayFromTupleDescriptor (TYPE_1__*) ; 
 int /*<<< orphan*/ * TypeOutputFunctions (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

FmgrInfo *
ColumnOutputFunctions(TupleDesc rowDescriptor, bool binaryFormat)
{
	uint32 columnCount = (uint32) rowDescriptor->natts;
	Oid *columnTypes = TypeArrayFromTupleDescriptor(rowDescriptor);
	FmgrInfo *outputFunctions =
		TypeOutputFunctions(columnCount, columnTypes, binaryFormat);

	return outputFunctions;
}