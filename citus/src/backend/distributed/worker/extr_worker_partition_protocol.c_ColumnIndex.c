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
typedef  int /*<<< orphan*/  TupleDesc ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_COLUMN ; 
 int /*<<< orphan*/  ERROR ; 
 int SPI_ERROR_NOATTRIBUTE ; 
 int SPI_fnumber (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 

__attribute__((used)) static int
ColumnIndex(TupleDesc rowDescriptor, const char *columnName)
{
	int columnIndex = SPI_fnumber(rowDescriptor, columnName);
	if (columnIndex == SPI_ERROR_NOATTRIBUTE)
	{
		ereport(ERROR, (errcode(ERRCODE_UNDEFINED_COLUMN),
						errmsg("could not find column name \"%s\"", columnName)));
	}

	Assert(columnIndex >= 1);
	return columnIndex;
}