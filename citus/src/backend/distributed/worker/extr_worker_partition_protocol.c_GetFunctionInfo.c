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
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  FmgrInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GetDefaultOpClass (scalar_t__,scalar_t__) ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,scalar_t__) ; 
 int /*<<< orphan*/  fmgr_info (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ get_opclass_family (scalar_t__) ; 
 scalar_t__ get_opclass_input_type (scalar_t__) ; 
 scalar_t__ get_opfamily_proc (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc0 (int) ; 

FmgrInfo *
GetFunctionInfo(Oid typeId, Oid accessMethodId, int16 procedureId)
{
	FmgrInfo *functionInfo = (FmgrInfo *) palloc0(sizeof(FmgrInfo));

	/* get default operator class from pg_opclass for datum type */
	Oid operatorClassId = GetDefaultOpClass(typeId, accessMethodId);

	Oid operatorFamilyId = get_opclass_family(operatorClassId);
	Oid operatorClassInputType = get_opclass_input_type(operatorClassId);

	Oid operatorId = get_opfamily_proc(operatorFamilyId, operatorClassInputType,
									   operatorClassInputType, procedureId);

	if (operatorId == InvalidOid)
	{
		ereport(ERROR, (errmsg("could not find function for data typeId %u", typeId)));
	}

	/* fill in the FmgrInfo struct using the operatorId */
	fmgr_info(operatorId, functionInfo);

	return functionInfo;
}