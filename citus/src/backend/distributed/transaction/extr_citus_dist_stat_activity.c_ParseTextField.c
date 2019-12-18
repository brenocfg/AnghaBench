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
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  CStringGetDatum (char*) ; 
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PQgetisnull (int /*<<< orphan*/ *,int,int) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  textin ; 

__attribute__((used)) static text *
ParseTextField(PGresult *result, int rowIndex, int colIndex)
{
	char *resultString = NULL;
	Datum resultStringDatum = 0;
	Datum textDatum = 0;

	if (PQgetisnull(result, rowIndex, colIndex))
	{
		return NULL;
	}

	resultString = PQgetvalue(result, rowIndex, colIndex);
	resultStringDatum = CStringGetDatum(resultString);
	textDatum = DirectFunctionCall1(textin, resultStringDatum);

	return (text *) DatumGetPointer(textDatum);
}