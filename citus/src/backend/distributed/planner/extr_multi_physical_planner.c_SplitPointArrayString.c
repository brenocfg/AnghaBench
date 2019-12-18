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
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/ * StringInfo ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidOid ; 
 char* OutputFunctionCall (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 int /*<<< orphan*/  fmgr_info (scalar_t__,int /*<<< orphan*/ *) ; 
 char* format_type_be (scalar_t__) ; 
 char* format_type_with_typemod (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getTypeOutputInfo (scalar_t__,scalar_t__*,int*) ; 
 scalar_t__ get_array_type (scalar_t__) ; 
 int /*<<< orphan*/ * makeStringInfo () ; 
 scalar_t__ palloc0 (int) ; 
 char* quote_literal_cstr (char*) ; 

__attribute__((used)) static StringInfo
SplitPointArrayString(ArrayType *splitPointObject, Oid columnType, int32 columnTypeMod)
{
	StringInfo splitPointArrayString = NULL;
	Datum splitPointDatum = PointerGetDatum(splitPointObject);
	Oid outputFunctionId = InvalidOid;
	bool typeVariableLength = false;
	FmgrInfo *arrayOutFunction = NULL;
	char *arrayOutputText = NULL;
	char *arrayOutputEscapedText = NULL;
	char *arrayOutTypeName = NULL;

	Oid arrayOutType = get_array_type(columnType);
	if (arrayOutType == InvalidOid)
	{
		char *columnTypeName = format_type_be(columnType);
		ereport(ERROR, (errmsg("cannot range repartition table on column type %s",
							   columnTypeName)));
	}

	arrayOutFunction = (FmgrInfo *) palloc0(sizeof(FmgrInfo));
	getTypeOutputInfo(arrayOutType, &outputFunctionId, &typeVariableLength);
	fmgr_info(outputFunctionId, arrayOutFunction);

	arrayOutputText = OutputFunctionCall(arrayOutFunction, splitPointDatum);
	arrayOutputEscapedText = quote_literal_cstr(arrayOutputText);

	/* add an explicit cast to array's string representation */
	arrayOutTypeName = format_type_with_typemod(arrayOutType, columnTypeMod);

	splitPointArrayString = makeStringInfo();
	appendStringInfo(splitPointArrayString, "%s::%s",
					 arrayOutputEscapedText, arrayOutTypeName);

	return splitPointArrayString;
}