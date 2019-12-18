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
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidOid ; 
 char* OidOutputFunctionCall (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getTypeOutputInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 

char *
DatumToString(Datum datum, Oid dataType)
{
	char *outputString = NULL;
	Oid typIoFunc = InvalidOid;
	bool typIsVarlena = false;

	getTypeOutputInfo(dataType, &typIoFunc, &typIsVarlena);
	outputString = OidOutputFunctionCall(typIoFunc, datum);

	return outputString;
}