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
typedef  int /*<<< orphan*/  TimestampTz ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  CStringGetDatum (char*) ; 
 int /*<<< orphan*/  DT_NOBEGIN ; 
 int /*<<< orphan*/  DatumGetTimestampTz (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ PQgetisnull (int /*<<< orphan*/ *,int,int) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  timestamptz_in ; 

TimestampTz
ParseTimestampTzField(PGresult *result, int rowIndex, int colIndex)
{
	char *resultString = NULL;
	Datum resultStringDatum = 0;
	Datum timestampDatum = 0;

	if (PQgetisnull(result, rowIndex, colIndex))
	{
		return DT_NOBEGIN;
	}

	resultString = PQgetvalue(result, rowIndex, colIndex);
	resultStringDatum = CStringGetDatum(resultString);
	timestampDatum = DirectFunctionCall3(timestamptz_in, resultStringDatum, 0, -1);

	return DatumGetTimestampTz(timestampDatum);
}