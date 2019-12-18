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
struct TYPE_3__ {int /*<<< orphan*/  typeName; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  const ObjectAddress ;
typedef  TYPE_1__ AlterEnumStmt ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  LookupTypeNameOid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ObjectAddressSet (int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TypeRelationId ; 
 int /*<<< orphan*/ * makeTypeNameFromNameList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* palloc0 (int) ; 

const ObjectAddress *
AlterEnumStmtObjectAddress(AlterEnumStmt *stmt, bool missing_ok)
{
	TypeName *typeName = NULL;
	Oid typeOid = InvalidOid;
	ObjectAddress *address = NULL;

	typeName = makeTypeNameFromNameList(stmt->typeName);
	typeOid = LookupTypeNameOid(NULL, typeName, missing_ok);
	address = palloc0(sizeof(ObjectAddress));
	ObjectAddressSet(*address, TypeRelationId, typeOid);

	return address;
}