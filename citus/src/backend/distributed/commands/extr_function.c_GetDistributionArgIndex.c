#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/ * HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROCOID ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ argumentStartsWith (char*,char*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 int get_func_arg_info (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char***,char**) ; 
 char* get_func_name (int /*<<< orphan*/ ) ; 
 int pg_atoi (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ pg_strncasecmp (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
GetDistributionArgIndex(Oid functionOid, char *distributionArgumentName,
						Oid *distributionArgumentOid)
{
	int distributionArgumentIndex = -1;

	int numberOfArgs = 0;
	int argIndex = 0;
	Oid *argTypes = NULL;
	char **argNames = NULL;
	char *argModes = NULL;

	HeapTuple proctup = NULL;

	*distributionArgumentOid = InvalidOid;

	proctup = SearchSysCache1(PROCOID, ObjectIdGetDatum(functionOid));
	if (!HeapTupleIsValid(proctup))
	{
		elog(ERROR, "cache lookup failed for function %u", functionOid);
	}

	numberOfArgs = get_func_arg_info(proctup, &argTypes, &argNames, &argModes);

	if (argumentStartsWith(distributionArgumentName, "$"))
	{
		/* skip the first character, we're safe because text_to_cstring pallocs */
		distributionArgumentName++;

		/* throws error if the input is not an integer */
		distributionArgumentIndex = pg_atoi(distributionArgumentName, 4, 0);

		if (distributionArgumentIndex < 1 || distributionArgumentIndex > numberOfArgs)
		{
			char *functionName = get_func_name(functionOid);

			ereport(ERROR, (errcode(ERRCODE_INVALID_PARAMETER_VALUE),
							errmsg("cannot distribute the function \"%s\" since "
								   "the distribution argument is not valid",
								   functionName),
							errhint("Either provide a valid function argument name "
									"or a valid \"$paramIndex\" to "
									"create_distributed_function()")));
		}

		/*
		 * Internal representation for the distributionArgumentIndex
		 * starts from 0 whereas user facing API starts from 1.
		 */
		distributionArgumentIndex -= 1;
		*distributionArgumentOid = argTypes[distributionArgumentIndex];

		ReleaseSysCache(proctup);

		Assert(*distributionArgumentOid != InvalidOid);

		return distributionArgumentIndex;
	}

	/*
	 * The user didn't provid "$paramIndex" but potentially the name of the paramater.
	 * So, loop over the arguments and try to find the argument name that matches
	 * the parameter that user provided.
	 */
	for (argIndex = 0; argIndex < numberOfArgs; ++argIndex)
	{
		char *argNameOnIndex = argNames != NULL ? argNames[argIndex] : NULL;

		if (argNameOnIndex != NULL &&
			pg_strncasecmp(argNameOnIndex, distributionArgumentName, NAMEDATALEN) == 0)
		{
			distributionArgumentIndex = argIndex;

			*distributionArgumentOid = argTypes[argIndex];

			/* we found, no need to continue */
			break;
		}
	}

	/* we still couldn't find the argument, so error out */
	if (distributionArgumentIndex == -1)
	{
		char *functionName = get_func_name(functionOid);

		ereport(ERROR, (errcode(ERRCODE_INVALID_PARAMETER_VALUE),
						errmsg("cannot distribute the function \"%s\" since the "
							   "distribution argument is not valid ", functionName),
						errhint("Either provide a valid function argument name "
								"or a valid \"$paramIndex\" to "
								"create_distributed_function()")));
	}

	ReleaseSysCache(proctup);

	Assert(*distributionArgumentOid != InvalidOid);

	return distributionArgumentIndex;
}