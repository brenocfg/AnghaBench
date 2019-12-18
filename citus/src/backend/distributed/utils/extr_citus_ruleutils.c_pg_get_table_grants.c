#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ ai_grantee; } ;
struct TYPE_11__ {int /*<<< orphan*/  rolname; } ;
struct TYPE_10__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  int /*<<< orphan*/ * Relation ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_2__* Form_pg_authid ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int AclMode ;
typedef  TYPE_3__ AclItem ;
typedef  int /*<<< orphan*/  Acl ;

/* Variables and functions */
 int ACLITEM_GET_GOPTIONS (TYPE_3__) ; 
 int ACLITEM_GET_PRIVS (TYPE_3__) ; 
 TYPE_3__* ACL_DAT (int /*<<< orphan*/ *) ; 
 int ACL_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AUTHOID ; 
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_class_relacl ; 
 int /*<<< orphan*/ * DatumGetAclP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_TABLE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ *) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NIL ; 
 int N_ACL_RIGHTS ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  RELOID ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,char*,...) ; 
 int /*<<< orphan*/  convert_aclright_to_string (int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,scalar_t__) ; 
 char* generate_relation_name (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pstrdup (int /*<<< orphan*/ ) ; 
 char* quote_identifier (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * relation_open (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resetStringInfo (TYPE_1__*) ; 

List *
pg_get_table_grants(Oid relationId)
{
	/* *INDENT-OFF* */
	StringInfoData buffer;
	Relation relation = NULL;
	char *relationName = NULL;
	List *defs = NIL;
	HeapTuple classTuple = NULL;
	Datum aclDatum = 0;
	bool isNull = false;

	relation = relation_open(relationId, AccessShareLock);
	relationName = generate_relation_name(relationId, NIL);

	initStringInfo(&buffer);

	/* lookup all table level grants */
	classTuple = SearchSysCache1(RELOID, ObjectIdGetDatum(relationId));
	if (!HeapTupleIsValid(classTuple))
	{
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_TABLE),
				 errmsg("relation with OID %u does not exist",
						relationId)));
	}

	aclDatum = SysCacheGetAttr(RELOID, classTuple, Anum_pg_class_relacl,
							   &isNull);

	ReleaseSysCache(classTuple);

	if (!isNull)
	{
		int i = 0;
		AclItem *aidat = NULL;
		Acl *acl = NULL;
		int offtype = 0;

		/*
		 * First revoke all default permissions, so we can start adding the
		 * exact permissions from the master. Note that we only do so if there
		 * are any actual grants; an empty grant set signals default
		 * permissions.
		 *
		 * Note: This doesn't work correctly if default permissions have been
		 * changed with ALTER DEFAULT PRIVILEGES - but that's hard to fix
		 * properly currently.
		 */
		appendStringInfo(&buffer, "REVOKE ALL ON %s FROM PUBLIC",
						 relationName);
		defs = lappend(defs, pstrdup(buffer.data));
		resetStringInfo(&buffer);

		/* iterate through the acl datastructure, emit GRANTs */

		acl = DatumGetAclP(aclDatum);
		aidat = ACL_DAT(acl);

		offtype = -1;
		i = 0;
		while (i < ACL_NUM(acl))
		{
			AclItem    *aidata = NULL;
			AclMode		priv_bit = 0;

			offtype++;

			if (offtype == N_ACL_RIGHTS)
			{
				offtype = 0;
				i++;
				if (i >= ACL_NUM(acl)) /* done */
				{
					break;
				}
			}

			aidata = &aidat[i];
			priv_bit = 1 << offtype;

			if (ACLITEM_GET_PRIVS(*aidata) & priv_bit)
			{
				const char *roleName = NULL;
				const char *withGrant = "";

				if (aidata->ai_grantee != 0)
				{
					HeapTuple htup;

					htup = SearchSysCache1(AUTHOID, ObjectIdGetDatum(aidata->ai_grantee));
					if (HeapTupleIsValid(htup))
					{
						Form_pg_authid authForm = ((Form_pg_authid) GETSTRUCT(htup));

						roleName = quote_identifier(NameStr(authForm->rolname));

						ReleaseSysCache(htup);
					}
					else
					{
						elog(ERROR, "cache lookup failed for role %u", aidata->ai_grantee);
					}
				}
				else
				{
					roleName = "PUBLIC";
				}

				if ((ACLITEM_GET_GOPTIONS(*aidata) & priv_bit) != 0)
				{
					withGrant = " WITH GRANT OPTION";
				}

				appendStringInfo(&buffer, "GRANT %s ON %s TO %s%s",
								 convert_aclright_to_string(priv_bit),
								 relationName,
								 roleName,
								 withGrant);

				defs = lappend(defs, pstrdup(buffer.data));

				resetStringInfo(&buffer);
			}
		}
	}

	resetStringInfo(&buffer);

	relation_close(relation, NoLock);
	return defs;
	/* *INDENT-ON* */
}