#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ aggkind; int aggnumdirectargs; scalar_t__ aggtransfn; char* aggtransspace; scalar_t__ aggfinalfn; int aggfinalmodify; char* aggmtransspace; scalar_t__ aggmfinalfn; scalar_t__ aggmtransfn; scalar_t__ aggminvtransfn; scalar_t__ aggcombinefn; scalar_t__ aggserialfn; scalar_t__ aggdeserialfn; scalar_t__ aggsortop; scalar_t__ aggmtranstype; scalar_t__ aggmfinalextra; scalar_t__ aggfinalextra; scalar_t__ aggtranstype; } ;
struct TYPE_9__ {scalar_t__ prokind; int proparallel; int /*<<< orphan*/  pronamespace; int /*<<< orphan*/  proname; } ;
struct TYPE_8__ {char* data; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  char RegProcedure ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_2__* Form_pg_proc ;
typedef  TYPE_3__* Form_pg_aggregate ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  AGGFNOID ; 
 scalar_t__ AGGKIND_HYPOTHETICAL ; 
 scalar_t__ AGGKIND_IS_ORDERED_SET (scalar_t__) ; 
#define  AGGMODIFY_READ_ONLY 135 
#define  AGGMODIFY_READ_WRITE 134 
#define  AGGMODIFY_SHAREABLE 133 
 int /*<<< orphan*/  Anum_pg_aggregate_agginitval ; 
 int /*<<< orphan*/  Anum_pg_aggregate_aggminitval ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 scalar_t__ InvalidOid ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
#define  PROARGMODE_IN 132 
#define  PROARGMODE_VARIADIC 131 
 int /*<<< orphan*/  PROCOID ; 
 scalar_t__ PROKIND_AGGREGATE ; 
#define  PROPARALLEL_RESTRICTED 130 
#define  PROPARALLEL_SAFE 129 
#define  PROPARALLEL_UNSAFE 128 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SearchSysCache1 (int /*<<< orphan*/ ,char const) ; 
 int /*<<< orphan*/  SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARNING ; 
 char* WrapCreateOrReplace (char*) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,char const*,...) ; 
 int /*<<< orphan*/  appendStringInfoChar (TYPE_1__*,char) ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char const) ; 
 char* format_type_be_qualified (scalar_t__) ; 
 char* generate_operator_name (scalar_t__,scalar_t__,scalar_t__) ; 
 int get_func_arg_info (int /*<<< orphan*/ *,scalar_t__**,char***,char**) ; 
 char* get_namespace_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 char* quote_identifier (char*) ; 
 char* quote_literal_cstr (char*) ; 
 char* quote_qualified_func_name (scalar_t__) ; 
 char* quote_qualified_identifier (char const*,char const*) ; 

__attribute__((used)) static char *
GetAggregateDDLCommand(const RegProcedure funcOid, bool useCreateOrReplace)
{
	StringInfoData buf = { 0 };
	HeapTuple proctup = NULL;
	Form_pg_proc proc = NULL;
	HeapTuple aggtup = NULL;
	Form_pg_aggregate agg = NULL;
	const char *name = NULL;
	const char *nsp = NULL;
	int numargs = 0;
	int i = 0;
	Oid *argtypes = NULL;
	char **argnames = NULL;
	char *argmodes = NULL;
	int insertorderbyat = -1;
	int argsprinted = 0;
	int inputargno = 0;

	proctup = SearchSysCache1(PROCOID, funcOid);
	if (!HeapTupleIsValid(proctup))
	{
		elog(ERROR, "cache lookup failed for %d", funcOid);
	}

	proc = (Form_pg_proc) GETSTRUCT(proctup);

	Assert(proc->prokind == PROKIND_AGGREGATE);

	initStringInfo(&buf);

	name = NameStr(proc->proname);
	nsp = get_namespace_name(proc->pronamespace);

#if PG_VERSION_NUM >= 120000
	if (useCreateOrReplace)
	{
		appendStringInfo(&buf, "CREATE OR REPLACE AGGREGATE %s(",
						 quote_qualified_identifier(nsp, name));
	}
	else
	{
		appendStringInfo(&buf, "CREATE AGGREGATE %s(",
						 quote_qualified_identifier(nsp, name));
	}
#else
	appendStringInfo(&buf, "CREATE AGGREGATE %s(",
					 quote_qualified_identifier(nsp, name));
#endif

	/* Parameters, borrows heavily from print_function_arguments in postgres */
	numargs = get_func_arg_info(proctup, &argtypes, &argnames, &argmodes);

	aggtup = SearchSysCache1(AGGFNOID, funcOid);
	if (!HeapTupleIsValid(aggtup))
	{
		elog(ERROR, "cache lookup failed for %d", funcOid);
	}
	agg = (Form_pg_aggregate) GETSTRUCT(aggtup);

	if (AGGKIND_IS_ORDERED_SET(agg->aggkind))
	{
		insertorderbyat = agg->aggnumdirectargs;
	}

	for (i = 0; i < numargs; i++)
	{
		Oid argtype = argtypes[i];
		char *argname = argnames ? argnames[i] : NULL;
		char argmode = argmodes ? argmodes[i] : PROARGMODE_IN;
		const char *modename;

		switch (argmode)
		{
			case PROARGMODE_IN:
			{
				modename = "";
				break;
			}

			case PROARGMODE_VARIADIC:
			{
				modename = "VARIADIC ";
				break;
			}

			default:
			{
				elog(ERROR, "unexpected parameter mode '%c'", argmode);
				modename = NULL;
				break;
			}
		}

		inputargno++;       /* this is a 1-based counter */
		if (argsprinted == insertorderbyat)
		{
			appendStringInfoString(&buf, " ORDER BY ");
		}
		else if (argsprinted)
		{
			appendStringInfoString(&buf, ", ");
		}

		appendStringInfoString(&buf, modename);

		if (argname && argname[0])
		{
			appendStringInfo(&buf, "%s ", quote_identifier(argname));
		}

		appendStringInfoString(&buf, format_type_be_qualified(argtype));

		argsprinted++;

		/* nasty hack: print the last arg twice for variadic ordered-set agg */
		if (argsprinted == insertorderbyat && i == numargs - 1)
		{
			i--;
		}
	}

	appendStringInfo(&buf, ") (STYPE = %s,SFUNC = %s",
					 format_type_be_qualified(agg->aggtranstype),
					 quote_qualified_func_name(agg->aggtransfn));

	if (agg->aggtransspace != 0)
	{
		appendStringInfo(&buf, ", SSPACE = %d", agg->aggtransspace);
	}

	if (agg->aggfinalfn != InvalidOid)
	{
		const char *finalmodifystring = NULL;
		switch (agg->aggfinalmodify)
		{
			case AGGMODIFY_READ_ONLY:
			{
				finalmodifystring = "READ_ONLY";
				break;
			}

			case AGGMODIFY_SHAREABLE:
			{
				finalmodifystring = "SHAREABLE";
				break;
			}

			case AGGMODIFY_READ_WRITE:
			{
				finalmodifystring = "READ_WRITE";
				break;
			}
		}

		appendStringInfo(&buf, ", FINALFUNC = %s",
						 quote_qualified_func_name(agg->aggfinalfn));

		if (finalmodifystring != NULL)
		{
			appendStringInfo(&buf, ", FINALFUNC_MODIFY = %s", finalmodifystring);
		}

		if (agg->aggfinalextra)
		{
			appendStringInfoString(&buf, ", FINALFUNC_EXTRA");
		}
	}

	if (agg->aggmtransspace != 0)
	{
		appendStringInfo(&buf, ", MSSPACE = %d", agg->aggmtransspace);
	}

	if (agg->aggmfinalfn)
	{
		const char *mfinalmodifystring = NULL;
		switch (agg->aggfinalmodify)
		{
			case AGGMODIFY_READ_ONLY:
			{
				mfinalmodifystring = "READ_ONLY";
				break;
			}

			case AGGMODIFY_SHAREABLE:
			{
				mfinalmodifystring = "SHAREABLE";
				break;
			}

			case AGGMODIFY_READ_WRITE:
			{
				mfinalmodifystring = "READ_WRITE";
				break;
			}
		}

		appendStringInfo(&buf, ", MFINALFUNC = %s",
						 quote_qualified_func_name(agg->aggmfinalfn));

		if (mfinalmodifystring != NULL)
		{
			appendStringInfo(&buf, ", MFINALFUNC_MODIFY = %s", mfinalmodifystring);
		}

		if (agg->aggmfinalextra)
		{
			appendStringInfoString(&buf, ", MFINALFUNC_EXTRA");
		}
	}

	if (agg->aggmtransfn)
	{
		appendStringInfo(&buf, ", MSFUNC = %s",
						 quote_qualified_func_name(agg->aggmtransfn));

		if (agg->aggmtranstype)
		{
			appendStringInfo(&buf, ", MSTYPE = %s",
							 format_type_be_qualified(agg->aggmtranstype));
		}
	}

	if (agg->aggtransspace != 0)
	{
		appendStringInfo(&buf, ", SSPACE = %d", agg->aggtransspace);
	}

	if (agg->aggminvtransfn)
	{
		appendStringInfo(&buf, ", MINVFUNC = %s",
						 quote_qualified_func_name(agg->aggminvtransfn));
	}

	if (agg->aggcombinefn)
	{
		appendStringInfo(&buf, ", COMBINEFUNC = %s",
						 quote_qualified_func_name(agg->aggcombinefn));
	}

	if (agg->aggserialfn)
	{
		appendStringInfo(&buf, ", SERIALFUNC = %s",
						 quote_qualified_func_name(agg->aggserialfn));
	}

	if (agg->aggdeserialfn)
	{
		appendStringInfo(&buf, ", DESERIALFUNC = %s",
						 quote_qualified_func_name(agg->aggdeserialfn));
	}

	if (agg->aggsortop != InvalidOid)
	{
		appendStringInfo(&buf, ", SORTOP = %s",
						 generate_operator_name(agg->aggsortop, argtypes[0],
												argtypes[0]));
	}

	{
		const char *parallelstring = NULL;
		switch (proc->proparallel)
		{
			case PROPARALLEL_SAFE:
			{
				parallelstring = "SAFE";
				break;
			}

			case PROPARALLEL_RESTRICTED:
			{
				parallelstring = "RESTRICTED";
				break;
			}

			case PROPARALLEL_UNSAFE:
			{
				break;
			}

			default:
			{
				elog(WARNING, "Unknown parallel option, ignoring: %c", proc->proparallel);
				break;
			}
		}

		if (parallelstring != NULL)
		{
			appendStringInfo(&buf, ", PARALLEL = %s", parallelstring);
		}
	}

	{
		bool isNull = false;
		Datum textInitVal = SysCacheGetAttr(AGGFNOID, aggtup,
											Anum_pg_aggregate_agginitval,
											&isNull);
		if (!isNull)
		{
			char *strInitVal = TextDatumGetCString(textInitVal);
			char *strInitValQuoted = quote_literal_cstr(strInitVal);

			appendStringInfo(&buf, ", INITCOND = %s", strInitValQuoted);

			pfree(strInitValQuoted);
			pfree(strInitVal);
		}
	}

	{
		bool isNull = false;
		Datum textInitVal = SysCacheGetAttr(AGGFNOID, aggtup,
											Anum_pg_aggregate_aggminitval,
											&isNull);
		if (!isNull)
		{
			char *strInitVal = TextDatumGetCString(textInitVal);
			char *strInitValQuoted = quote_literal_cstr(strInitVal);

			appendStringInfo(&buf, ", MINITCOND = %s", strInitValQuoted);

			pfree(strInitValQuoted);
			pfree(strInitVal);
		}
	}

	if (agg->aggkind == AGGKIND_HYPOTHETICAL)
	{
		appendStringInfoString(&buf, ", HYPOTHETICAL");
	}

	appendStringInfoChar(&buf, ')');

	ReleaseSysCache(aggtup);
	ReleaseSysCache(proctup);

#if PG_VERSION_NUM < 120000
	if (useCreateOrReplace)
	{
		return WrapCreateOrReplace(buf.data);
	}
#endif
	return buf.data;
}