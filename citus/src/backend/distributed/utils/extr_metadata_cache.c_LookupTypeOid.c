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
typedef  int /*<<< orphan*/  Value ;
typedef  int /*<<< orphan*/  TypeName ;
typedef  int /*<<< orphan*/ * Type ;
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__* Form_pg_type ;

/* Variables and functions */
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HeapTupleGetOid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/ * LookupTypeName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_make2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * makeString (char*) ; 
 int /*<<< orphan*/ * makeTypeNameFromNameList (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Oid
LookupTypeOid(char *typeNameString)
{
	Value *schemaName = makeString("pg_catalog");
	Value *typeName = makeString(typeNameString);
	List *qualifiedName = list_make2(schemaName, typeName);
	TypeName *enumTypeName = makeTypeNameFromNameList(qualifiedName);

	Oid nodeRoleTypId;

	/* typenameTypeId but instead of raising an error return InvalidOid */
	Type tup = LookupTypeName(NULL, enumTypeName, NULL, false);
	if (tup == NULL)
	{
		return InvalidOid;
	}

#if PG_VERSION_NUM >= 120000
	nodeRoleTypId = ((Form_pg_type) GETSTRUCT(tup))->oid;
#else
	nodeRoleTypId = HeapTupleGetOid(tup);
#endif
	ReleaseSysCache(tup);

	return nodeRoleTypId;
}