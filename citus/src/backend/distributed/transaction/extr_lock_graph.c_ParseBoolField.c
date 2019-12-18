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
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 scalar_t__ PQgetisnull (int /*<<< orphan*/ *,int,int) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int strlen (char*) ; 

bool
ParseBoolField(PGresult *result, int rowIndex, int colIndex)
{
	char *resultString = NULL;

	if (PQgetisnull(result, rowIndex, colIndex))
	{
		return false;
	}

	resultString = PQgetvalue(result, rowIndex, colIndex);
	if (strlen(resultString) != 1)
	{
		return false;
	}

	return resultString[0] == 't';
}