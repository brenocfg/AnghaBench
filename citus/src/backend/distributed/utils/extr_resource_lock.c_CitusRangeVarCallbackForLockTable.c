#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  relname; } ;
typedef  TYPE_1__ RangeVar ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  LOCKMODE ;
typedef  scalar_t__ AclResult ;

/* Variables and functions */
 scalar_t__ ACLCHECK_OK ; 
 scalar_t__ CitusLockTableAclCheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegularTable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aclcheck_error (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rel_relkind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_relkind_objtype (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
CitusRangeVarCallbackForLockTable(const RangeVar *rangeVar, Oid relationId,
								  Oid oldRelationId, void *arg)
{
	LOCKMODE lockmode = *(LOCKMODE *) arg;
	AclResult aclResult;

	if (!OidIsValid(relationId))
	{
		/* table doesn't exist, so no permissions check */
		return;
	}

	/* we only allow tables and views to be locked */
	if (!RegularTable(relationId))
	{
		ereport(ERROR, (errcode(ERRCODE_WRONG_OBJECT_TYPE),
						errmsg("\"%s\" is not a table", rangeVar->relname)));
	}

	/* check permissions */
	aclResult = CitusLockTableAclCheck(relationId, lockmode, GetUserId());
	if (aclResult != ACLCHECK_OK)
	{
		aclcheck_error(aclResult, get_relkind_objtype(get_rel_relkind(relationId)),
					   rangeVar->relname);
	}
}