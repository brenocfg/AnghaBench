#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
typedef  TYPE_2__* TupleDesc ;
struct TYPE_26__ {size_t num_defval; size_t num_check; TYPE_9__* check; TYPE_10__* defval; } ;
typedef  TYPE_3__ TupleConstr ;
struct TYPE_32__ {char* ccname; int /*<<< orphan*/  ccbin; } ;
struct TYPE_31__ {char* servername; } ;
struct TYPE_30__ {int /*<<< orphan*/  options; int /*<<< orphan*/  serverid; } ;
struct TYPE_29__ {scalar_t__ attgenerated; scalar_t__ attcollation; scalar_t__ attnotnull; scalar_t__ atthasdef; int /*<<< orphan*/  atttypmod; int /*<<< orphan*/  atttypid; int /*<<< orphan*/  attname; int /*<<< orphan*/  attisdropped; } ;
struct TYPE_28__ {TYPE_1__* rd_rel; } ;
struct TYPE_27__ {char* data; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
struct TYPE_25__ {int natts; TYPE_3__* constr; } ;
struct TYPE_24__ {scalar_t__ relpersistence; char relkind; } ;
struct TYPE_23__ {int adnum; int /*<<< orphan*/  adbin; } ;
typedef  TYPE_4__ StringInfoData ;
typedef  TYPE_5__* Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_6__* Form_pg_attribute ;
typedef  TYPE_7__ ForeignTable ;
typedef  TYPE_8__ ForeignServer ;
typedef  TYPE_9__ ConstrCheck ;
typedef  size_t AttrNumber ;
typedef  TYPE_10__ AttrDefault ;

/* Variables and functions */
 scalar_t__ ATTRIBUTE_GENERATED_STORED ; 
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  AppendOptionListToString (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DEFAULT_COLLATION_OID ; 
 int /*<<< orphan*/  EnsureRelationKindSupported (int /*<<< orphan*/ ) ; 
 char* GeneratePartitioningInformation (int /*<<< orphan*/ ) ; 
 TYPE_8__* GetForeignServer (int /*<<< orphan*/ ) ; 
 TYPE_7__* GetForeignTable (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  NIL ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 char RELKIND_FOREIGN_TABLE ; 
 char RELKIND_PARTITIONED_TABLE ; 
 scalar_t__ RELPERSISTENCE_UNLOGGED ; 
 scalar_t__ RegularTable (int /*<<< orphan*/ ) ; 
 TYPE_2__* RelationGetDescr (TYPE_5__*) ; 
 TYPE_6__* TupleDescAttr (TYPE_2__*,int) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_4__*,char*,char*) ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_4__*,char const*) ; 
 int /*<<< orphan*/  contain_nextval_expression_walker (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * deparse_context_for (char*,int /*<<< orphan*/ ) ; 
 char* deparse_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 char* flatten_reloptions (int /*<<< orphan*/ ) ; 
 char* format_type_with_typemod (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* generate_collation_name (scalar_t__) ; 
 char* generate_relation_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_4__*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 char* quote_identifier (char const*) ; 
 int /*<<< orphan*/  relation_close (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* relation_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stringToNode (int /*<<< orphan*/ ) ; 

char *
pg_get_tableschemadef_string(Oid tableRelationId, bool includeSequenceDefaults)
{
	Relation relation = NULL;
	char *relationName = NULL;
	char relationKind = 0;
	TupleDesc tupleDescriptor = NULL;
	TupleConstr *tupleConstraints = NULL;
	int attributeIndex = 0;
	bool firstAttributePrinted = false;
	AttrNumber defaultValueIndex = 0;
	AttrNumber constraintIndex = 0;
	AttrNumber constraintCount = 0;
	StringInfoData buffer = { NULL, 0, 0, 0 };

	/*
	 * Instead of retrieving values from system catalogs as other functions in
	 * ruleutils.c do, we follow an unusual approach here: we open the relation,
	 * and fetch the relation's tuple descriptor. We do this because the tuple
	 * descriptor already contains information harnessed from pg_attrdef,
	 * pg_attribute, pg_constraint, and pg_class; and therefore using the
	 * descriptor saves us from a lot of additional work.
	 */
	relation = relation_open(tableRelationId, AccessShareLock);
	relationName = generate_relation_name(tableRelationId, NIL);

	EnsureRelationKindSupported(tableRelationId);

	initStringInfo(&buffer);

	if (RegularTable(tableRelationId))
	{
		appendStringInfoString(&buffer, "CREATE ");

		if (relation->rd_rel->relpersistence == RELPERSISTENCE_UNLOGGED)
		{
			appendStringInfoString(&buffer, "UNLOGGED ");
		}

		appendStringInfo(&buffer, "TABLE %s (", relationName);
	}
	else
	{
		appendStringInfo(&buffer, "CREATE FOREIGN TABLE %s (", relationName);
	}

	/*
	 * Iterate over the table's columns. If a particular column is not dropped
	 * and is not inherited from another table, print the column's name and its
	 * formatted type.
	 */
	tupleDescriptor = RelationGetDescr(relation);
	tupleConstraints = tupleDescriptor->constr;

	for (attributeIndex = 0; attributeIndex < tupleDescriptor->natts; attributeIndex++)
	{
		Form_pg_attribute attributeForm = TupleDescAttr(tupleDescriptor, attributeIndex);

		/*
		 * We disregard the inherited attributes (i.e., attinhcount > 0) here. The
		 * reasoning behind this is that Citus implements declarative partitioning
		 * by creating the partitions first and then sending
		 * "ALTER TABLE parent_table ATTACH PARTITION .." command. This may not play
		 * well with regular inherited tables, which isn't a big concern from Citus'
		 * perspective.
		 */
		if (!attributeForm->attisdropped)
		{
			const char *attributeName = NULL;
			const char *attributeTypeName = NULL;

			if (firstAttributePrinted)
			{
				appendStringInfoString(&buffer, ", ");
			}
			firstAttributePrinted = true;

			attributeName = NameStr(attributeForm->attname);
			appendStringInfo(&buffer, "%s ", quote_identifier(attributeName));

			attributeTypeName = format_type_with_typemod(attributeForm->atttypid,
														 attributeForm->atttypmod);
			appendStringInfoString(&buffer, attributeTypeName);

			/* if this column has a default value, append the default value */
			if (attributeForm->atthasdef)
			{
				AttrDefault *defaultValueList = NULL;
				AttrDefault *defaultValue = NULL;

				Node *defaultNode = NULL;
				List *defaultContext = NULL;
				char *defaultString = NULL;

				Assert(tupleConstraints != NULL);

				defaultValueList = tupleConstraints->defval;
				Assert(defaultValueList != NULL);

				defaultValue = &(defaultValueList[defaultValueIndex]);
				defaultValueIndex++;

				Assert(defaultValue->adnum == (attributeIndex + 1));
				Assert(defaultValueIndex <= tupleConstraints->num_defval);

				/* convert expression to node tree, and prepare deparse context */
				defaultNode = (Node *) stringToNode(defaultValue->adbin);

				/*
				 * if column default value is explicitly requested, or it is
				 * not set from a sequence then we include DEFAULT clause for
				 * this column.
				 */
				if (includeSequenceDefaults ||
					!contain_nextval_expression_walker(defaultNode, NULL))
				{
					defaultContext = deparse_context_for(relationName, tableRelationId);

					/* deparse default value string */
					defaultString = deparse_expression(defaultNode, defaultContext,
													   false, false);

#if PG_VERSION_NUM >= 120000
					if (attributeForm->attgenerated == ATTRIBUTE_GENERATED_STORED)
					{
						appendStringInfo(&buffer, " GENERATED ALWAYS AS (%s) STORED",
										 defaultString);
					}
					else
					{
						appendStringInfo(&buffer, " DEFAULT %s", defaultString);
					}
#else
					appendStringInfo(&buffer, " DEFAULT %s", defaultString);
#endif
				}
			}

			/* if this column has a not null constraint, append the constraint */
			if (attributeForm->attnotnull)
			{
				appendStringInfoString(&buffer, " NOT NULL");
			}

			if (attributeForm->attcollation != InvalidOid &&
				attributeForm->attcollation != DEFAULT_COLLATION_OID)
			{
				appendStringInfo(&buffer, " COLLATE %s", generate_collation_name(
									 attributeForm->attcollation));
			}
		}
	}

	/*
	 * Now check if the table has any constraints. If it does, set the number of
	 * check constraints here. Then iterate over all check constraints and print
	 * them.
	 */
	if (tupleConstraints != NULL)
	{
		constraintCount = tupleConstraints->num_check;
	}

	for (constraintIndex = 0; constraintIndex < constraintCount; constraintIndex++)
	{
		ConstrCheck *checkConstraintList = tupleConstraints->check;
		ConstrCheck *checkConstraint = &(checkConstraintList[constraintIndex]);

		Node *checkNode = NULL;
		List *checkContext = NULL;
		char *checkString = NULL;

		/* if an attribute or constraint has been printed, format properly */
		if (firstAttributePrinted || constraintIndex > 0)
		{
			appendStringInfoString(&buffer, ", ");
		}

		appendStringInfo(&buffer, "CONSTRAINT %s CHECK ",
						 quote_identifier(checkConstraint->ccname));

		/* convert expression to node tree, and prepare deparse context */
		checkNode = (Node *) stringToNode(checkConstraint->ccbin);
		checkContext = deparse_context_for(relationName, tableRelationId);

		/* deparse check constraint string */
		checkString = deparse_expression(checkNode, checkContext, false, false);

		appendStringInfoString(&buffer, checkString);
	}

	/* close create table's outer parentheses */
	appendStringInfoString(&buffer, ")");

	/*
	 * If the relation is a foreign table, append the server name and options to
	 * the create table statement.
	 */
	relationKind = relation->rd_rel->relkind;
	if (relationKind == RELKIND_FOREIGN_TABLE)
	{
		ForeignTable *foreignTable = GetForeignTable(tableRelationId);
		ForeignServer *foreignServer = GetForeignServer(foreignTable->serverid);

		char *serverName = foreignServer->servername;
		appendStringInfo(&buffer, " SERVER %s", quote_identifier(serverName));
		AppendOptionListToString(&buffer, foreignTable->options);
	}
	else if (relationKind == RELKIND_PARTITIONED_TABLE)
	{
		char *partitioningInformation = GeneratePartitioningInformation(tableRelationId);
		appendStringInfo(&buffer, " PARTITION BY %s ", partitioningInformation);
	}

	/*
	 * Add any reloptions (storage parameters) defined on the table in a WITH
	 * clause.
	 */
	{
		char *reloptions = flatten_reloptions(tableRelationId);
		if (reloptions)
		{
			appendStringInfo(&buffer, " WITH (%s)", reloptions);
			pfree(reloptions);
		}
	}

	relation_close(relation, AccessShareLock);

	return (buffer.data);
}