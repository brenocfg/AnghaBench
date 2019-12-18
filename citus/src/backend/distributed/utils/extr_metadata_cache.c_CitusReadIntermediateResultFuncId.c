#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ readIntermediateResultFuncId; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 scalar_t__ CitusCopyFormatTypeId () ; 
 scalar_t__ InvalidOid ; 
 scalar_t__ LookupFuncName (int /*<<< orphan*/ *,int,scalar_t__*,int) ; 
 TYPE_1__ MetadataCache ; 
 scalar_t__ TEXTOID ; 
 int /*<<< orphan*/ * list_make2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeString (char*) ; 

Oid
CitusReadIntermediateResultFuncId(void)
{
	if (MetadataCache.readIntermediateResultFuncId == InvalidOid)
	{
		List *functionNameList = list_make2(makeString("pg_catalog"),
											makeString("read_intermediate_result"));
		Oid copyFormatTypeOid = CitusCopyFormatTypeId();
		Oid paramOids[2] = { TEXTOID, copyFormatTypeOid };
		bool missingOK = false;

		MetadataCache.readIntermediateResultFuncId =
			LookupFuncName(functionNameList, 2, paramOids, missingOK);
	}

	return MetadataCache.readIntermediateResultFuncId;
}