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
typedef  int /*<<< orphan*/  Value ;
typedef  int /*<<< orphan*/  TypeName ;
struct TYPE_3__ {scalar_t__ objectType; scalar_t__ object; int /*<<< orphan*/  newschema; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  const ObjectAddress ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ AlterObjectSchemaStmt ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidOid ; 
 scalar_t__ LookupTypeNameOid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * NIL ; 
 scalar_t__ OBJECT_TYPE ; 
 int /*<<< orphan*/  ObjectAddressSet (int /*<<< orphan*/  const,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TypeNameToString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TypeRelationId ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lfirst (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_make2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_tail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  makeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * makeTypeNameFromNameList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* palloc0 (int) ; 

const ObjectAddress *
AlterTypeSchemaStmtObjectAddress(AlterObjectSchemaStmt *stmt, bool missing_ok)
{
	ObjectAddress *address = NULL;
	TypeName *typeName = NULL;
	Oid typeOid = InvalidOid;
	List *names = NIL;

	Assert(stmt->objectType == OBJECT_TYPE);

	names = (List *) stmt->object;

	/*
	 * we hardcode missing_ok here during LookupTypeNameOid because if we can't find it it
	 * might have already been moved in this transaction.
	 */
	typeName = makeTypeNameFromNameList(names);
	typeOid = LookupTypeNameOid(NULL, typeName, true);

	if (typeOid == InvalidOid)
	{
		/*
		 * couldn't find the type, might have already been moved to the new schema, we
		 * construct a new typename that uses the new schema to search in.
		 */

		/* typename is the last in the list of names */
		Value *typeNameStr = lfirst(list_tail(names));

		/*
		 * we don't error here either, as the error would be not a good user facing
		 * error if the type didn't exist in the first place.
		 */
		names = list_make2(makeString(stmt->newschema), typeNameStr);
		typeName = makeTypeNameFromNameList(names);
		typeOid = LookupTypeNameOid(NULL, typeName, true);

		/*
		 * if the type is still invalid we couldn't find the type, error with the same
		 * message postgres would error with it missing_ok is false (not ok to miss)
		 */
		if (!missing_ok && typeOid == InvalidOid)
		{
			names = (List *) stmt->object;
			typeName = makeTypeNameFromNameList(names);

			ereport(ERROR, (errcode(ERRCODE_UNDEFINED_OBJECT),
							errmsg("type \"%s\" does not exist",
								   TypeNameToString(typeName))));
		}
	}

	address = palloc0(sizeof(ObjectAddress));
	ObjectAddressSet(*address, TypeRelationId, typeOid);

	return address;
}