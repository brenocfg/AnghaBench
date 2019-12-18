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
typedef  int int32 ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  OidInputFunctionCall (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  getBaseTypeAndTypmod (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  getTypeInputInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

Datum
StringToDatum(char *inputString, Oid dataType)
{
	Oid typIoFunc = InvalidOid;
	Oid typIoParam = InvalidOid;
	int32 typeModifier = -1;
	Datum datum = 0;

	getTypeInputInfo(dataType, &typIoFunc, &typIoParam);
	getBaseTypeAndTypmod(dataType, &typeModifier);

	datum = OidInputFunctionCall(typIoFunc, inputString, typIoParam, typeModifier);

	return datum;
}