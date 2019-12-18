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
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  int16 ;
typedef  int /*<<< orphan*/ * StringInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_OUT_FUNC_ID ; 
 char* DatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * construct_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char) ; 
 int /*<<< orphan*/  fmgr_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_typlenbyvalalign (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,char*) ; 
 int /*<<< orphan*/ * makeStringInfo () ; 
 scalar_t__ palloc0 (int) ; 

__attribute__((used)) static StringInfo
DatumArrayString(Datum *datumArray, uint32 datumCount, Oid datumTypeId)
{
	StringInfo arrayStringInfo = NULL;
	FmgrInfo *arrayOutFunction = NULL;
	ArrayType *arrayObject = NULL;
	Datum arrayObjectDatum = 0;
	Datum arrayStringDatum = 0;
	char *arrayString = NULL;
	int16 typeLength = 0;
	bool typeByValue = false;
	char typeAlignment = 0;

	/* construct the array object from the given array */
	get_typlenbyvalalign(datumTypeId, &typeLength, &typeByValue, &typeAlignment);
	arrayObject = construct_array(datumArray, datumCount, datumTypeId,
								  typeLength, typeByValue, typeAlignment);
	arrayObjectDatum = PointerGetDatum(arrayObject);

	/* convert the array object to its string representation */
	arrayOutFunction = (FmgrInfo *) palloc0(sizeof(FmgrInfo));
	fmgr_info(ARRAY_OUT_FUNC_ID, arrayOutFunction);

	arrayStringDatum = FunctionCall1(arrayOutFunction, arrayObjectDatum);
	arrayString = DatumGetCString(arrayStringDatum);

	arrayStringInfo = makeStringInfo();
	appendStringInfo(arrayStringInfo, "%s", arrayString);

	return arrayStringInfo;
}