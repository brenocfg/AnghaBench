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
typedef  int /*<<< orphan*/  Var ;
struct TYPE_2__ {scalar_t__ attnum; int /*<<< orphan*/  attcollation; int /*<<< orphan*/  atttypmod; int /*<<< orphan*/  atttypid; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_1__* Form_pg_attribute ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_COLUMN ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 char* RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SearchSysCacheAttName (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*,char*) ; 
 int /*<<< orphan*/ * makeVar (int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  truncate_identifier (char*,int /*<<< orphan*/ ,int) ; 

Var *
BuildDistributionKeyFromColumnName(Relation distributedRelation, char *columnName)
{
	HeapTuple columnTuple = NULL;
	Form_pg_attribute columnForm = NULL;
	Var *distributionColumn = NULL;
	char *tableName = RelationGetRelationName(distributedRelation);

	/* short circuit for reference tables */
	if (columnName == NULL)
	{
		return NULL;
	}

	/* it'd probably better to downcase identifiers consistent with SQL case folding */
	truncate_identifier(columnName, strlen(columnName), true);

	/* lookup column definition */
	columnTuple = SearchSysCacheAttName(RelationGetRelid(distributedRelation),
										columnName);
	if (!HeapTupleIsValid(columnTuple))
	{
		ereport(ERROR, (errcode(ERRCODE_UNDEFINED_COLUMN),
						errmsg("column \"%s\" of relation \"%s\" does not exist",
							   columnName, tableName)));
	}

	columnForm = (Form_pg_attribute) GETSTRUCT(columnTuple);

	/* check if the column may be referenced in the distribution key */
	if (columnForm->attnum <= 0)
	{
		ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						errmsg("cannot reference system column \"%s\" in relation \"%s\"",
							   columnName, tableName)));
	}

	/* build Var referencing only the chosen distribution column */
	distributionColumn = makeVar(1, columnForm->attnum, columnForm->atttypid,
								 columnForm->atttypmod, columnForm->attcollation, 0);

	ReleaseSysCache(columnTuple);

	return distributionColumn;
}