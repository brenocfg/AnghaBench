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
typedef  int /*<<< orphan*/  TimestampTz ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  DT_NOBEGIN ; 
 int /*<<< orphan*/  DatumGetTimestampTz (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_getbinval (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static TimestampTz
ParseTimestampTzFieldFromHeapTuple(HeapTuple tuple, TupleDesc tupdesc, int colIndex)
{
	Datum resultDatum;
	bool isNull = false;

	resultDatum = SPI_getbinval(tuple, tupdesc, colIndex, &isNull);
	if (isNull)
	{
		return DT_NOBEGIN;
	}

	return DatumGetTimestampTz(resultDatum);
}