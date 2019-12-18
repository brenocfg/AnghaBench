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
typedef  int /*<<< orphan*/  int16 ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 int /*<<< orphan*/  ARR_ELEMTYPE (int /*<<< orphan*/ *) ; 
 int ARR_HASNULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERRCODE_NULL_VALUE_NOT_ALLOWED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  deconstruct_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char,int /*<<< orphan*/ **,int**,int*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  get_typlenbyvalalign (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,char*) ; 

Datum *
DeconstructArrayObject(ArrayType *arrayObject)
{
	Datum *datumArray = NULL;
	bool *datumArrayNulls = NULL;
	int datumArrayLength = 0;

	Oid typeId = InvalidOid;
	bool typeByVal = false;
	char typeAlign = 0;
	int16 typeLength = 0;

	bool arrayHasNull = ARR_HASNULL(arrayObject);
	if (arrayHasNull)
	{
		ereport(ERROR, (errcode(ERRCODE_NULL_VALUE_NOT_ALLOWED),
						errmsg("worker array object cannot contain null values")));
	}

	typeId = ARR_ELEMTYPE(arrayObject);
	get_typlenbyvalalign(typeId, &typeLength, &typeByVal, &typeAlign);

	deconstruct_array(arrayObject, typeId, typeLength, typeByVal, typeAlign,
					  &datumArray, &datumArrayNulls, &datumArrayLength);

	return datumArray;
}