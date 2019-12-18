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
struct TYPE_3__ {int /*<<< orphan*/  oid; int /*<<< orphan*/ * next; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__* FuncCandidateList ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_AMBIGUOUS_FUNCTION ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_FUNCTION ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_1__* FuncnameGetCandidates (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int const,int const,int) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 char* quote_qualified_identifier (char const*,char const*) ; 
 int /*<<< orphan*/ * stringToQualifiedNameList (char*) ; 

Oid
FunctionOidExtended(const char *schemaName, const char *functionName, int argumentCount,
					bool missingOK)
{
	FuncCandidateList functionList = NULL;
	Oid functionOid = InvalidOid;

	char *qualifiedFunctionName = quote_qualified_identifier(schemaName, functionName);
	List *qualifiedFunctionNameList = stringToQualifiedNameList(qualifiedFunctionName);
	List *argumentList = NIL;
	const bool findVariadics = false;
	const bool findDefaults = false;

	functionList = FuncnameGetCandidates(qualifiedFunctionNameList, argumentCount,
										 argumentList, findVariadics,
										 findDefaults, true);

	if (functionList == NULL)
	{
		if (missingOK)
		{
			return InvalidOid;
		}

		ereport(ERROR, (errcode(ERRCODE_UNDEFINED_FUNCTION),
						errmsg("function \"%s\" does not exist", functionName)));
	}
	else if (functionList->next != NULL)
	{
		ereport(ERROR, (errcode(ERRCODE_AMBIGUOUS_FUNCTION),
						errmsg("more than one function named \"%s\"", functionName)));
	}

	/* get function oid from function list's head */
	functionOid = functionList->oid;

	return functionOid;
}