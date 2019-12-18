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
typedef  int /*<<< orphan*/  TypeName ;
struct TYPE_3__ {scalar_t__ renameType; scalar_t__ relationType; int /*<<< orphan*/  relation; } ;
typedef  TYPE_1__ RenameStmt ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  const ObjectAddress ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  LookupTypeNameOid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * MakeTypeNameFromRangeVar (int /*<<< orphan*/ ) ; 
 scalar_t__ OBJECT_ATTRIBUTE ; 
 scalar_t__ OBJECT_TYPE ; 
 int /*<<< orphan*/  ObjectAddressSet (int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TypeRelationId ; 
 int /*<<< orphan*/  const* palloc0 (int) ; 

const ObjectAddress *
RenameTypeAttributeStmtObjectAddress(RenameStmt *stmt, bool missing_ok)
{
	TypeName *typeName = NULL;
	Oid typeOid = InvalidOid;
	ObjectAddress *address = NULL;

	Assert(stmt->renameType == OBJECT_ATTRIBUTE);
	Assert(stmt->relationType == OBJECT_TYPE);

	typeName = MakeTypeNameFromRangeVar(stmt->relation);
	typeOid = LookupTypeNameOid(NULL, typeName, missing_ok);
	address = palloc0(sizeof(ObjectAddress));
	ObjectAddressSet(*address, TypeRelationId, typeOid);

	return address;
}