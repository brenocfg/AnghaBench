#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ objectSubId; int /*<<< orphan*/  objectId; int /*<<< orphan*/  classId; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* StringInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ ObjectAddress ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ACLCHECK_NOT_OWNER ; 
 int /*<<< orphan*/  Anum_pg_namespace_oid ; 
 int /*<<< orphan*/  CStringGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  DEBUG2 ; 
 int /*<<< orphan*/  DROP_CASCADE ; 
 int /*<<< orphan*/  DROP_RESTRICT ; 
 int /*<<< orphan*/  GetSysCacheOid1Compat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  NAMESPACENAME ; 
 int /*<<< orphan*/  NamespaceRelationId ; 
 int /*<<< orphan*/  OBJECT_SCHEMA ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int PERFORM_DELETION_INTERNAL ; 
 int PERFORM_DELETION_QUIETLY ; 
 int PERFORM_DELETION_SKIP_EXTENSIONS ; 
 int PERFORM_DELETION_SKIP_ORIGINAL ; 
 int /*<<< orphan*/  aclcheck_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  performDeletion (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int pg_namespace_ownercheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
RemoveJobSchema(StringInfo schemaName)
{
	Datum schemaNameDatum = CStringGetDatum(schemaName->data);
	Oid schemaId = InvalidOid;

	schemaId = GetSysCacheOid1Compat(NAMESPACENAME, Anum_pg_namespace_oid,
									 schemaNameDatum);
	if (OidIsValid(schemaId))
	{
		ObjectAddress schemaObject = { 0, 0, 0 };

		bool permissionsOK = pg_namespace_ownercheck(schemaId, GetUserId());
		if (!permissionsOK)
		{
			aclcheck_error(ACLCHECK_NOT_OWNER, OBJECT_SCHEMA, schemaName->data);
		}

		schemaObject.classId = NamespaceRelationId;
		schemaObject.objectId = schemaId;
		schemaObject.objectSubId = 0;

		/*
		 * We first delete all tables in this schema. Rather than relying on the
		 * schema command, we call the dependency mechanism directly so that we
		 * can suppress notice messages that are typically displayed during
		 * cascading deletes.
		 */
		performDeletion(&schemaObject, DROP_CASCADE,
						PERFORM_DELETION_INTERNAL |
						PERFORM_DELETION_QUIETLY |
						PERFORM_DELETION_SKIP_ORIGINAL |
						PERFORM_DELETION_SKIP_EXTENSIONS);

		CommandCounterIncrement();

		/* drop the empty schema */
		performDeletion(&schemaObject, DROP_RESTRICT, 0);
		CommandCounterIncrement();
	}
	else
	{
		ereport(DEBUG2, (errmsg("schema \"%s\" does not exist, skipping",
								schemaName->data)));
	}
}