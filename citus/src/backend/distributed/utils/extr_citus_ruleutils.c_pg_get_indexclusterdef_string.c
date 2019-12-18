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
struct TYPE_6__ {scalar_t__ indisclustered; int /*<<< orphan*/  indrelid; } ;
struct TYPE_5__ {char* data; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_2__* Form_pg_index ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INDEXRELID ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SearchSysCache (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 char* generate_relation_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* get_rel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  quote_identifier (char*) ; 

char *
pg_get_indexclusterdef_string(Oid indexRelationId)
{
	HeapTuple indexTuple = NULL;
	Form_pg_index indexForm = NULL;
	Oid tableRelationId = InvalidOid;
	StringInfoData buffer = { NULL, 0, 0, 0 };

	indexTuple = SearchSysCache(INDEXRELID, ObjectIdGetDatum(indexRelationId), 0, 0, 0);
	if (!HeapTupleIsValid(indexTuple))
	{
		ereport(ERROR, (errmsg("cache lookup failed for index %u", indexRelationId)));
	}

	indexForm = (Form_pg_index) GETSTRUCT(indexTuple);
	tableRelationId = indexForm->indrelid;

	/* check if the table is clustered on this index */
	if (indexForm->indisclustered)
	{
		char *tableName = generate_relation_name(tableRelationId, NIL);
		char *indexName = get_rel_name(indexRelationId); /* needs to be quoted */

		initStringInfo(&buffer);
		appendStringInfo(&buffer, "ALTER TABLE %s CLUSTER ON %s",
						 tableName, quote_identifier(indexName));
	}

	ReleaseSysCache(indexTuple);

	return (buffer.data);
}