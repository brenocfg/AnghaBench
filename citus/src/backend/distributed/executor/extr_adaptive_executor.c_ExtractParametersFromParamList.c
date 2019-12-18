#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ ptype; int /*<<< orphan*/  value; scalar_t__ isnull; } ;
struct TYPE_4__ {int numParams; TYPE_2__* params; } ;
typedef  TYPE_1__* ParamListInfo ;
typedef  TYPE_2__ ParamExternData ;
typedef  scalar_t__ Oid ;

/* Variables and functions */
 scalar_t__ FirstNormalObjectId ; 
 scalar_t__ InvalidOid ; 
 char* OidOutputFunctionCall (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ TEXTOID ; 
 int /*<<< orphan*/  getTypeOutputInfo (scalar_t__,scalar_t__*,int*) ; 
 scalar_t__ palloc0 (int) ; 

void
ExtractParametersFromParamList(ParamListInfo paramListInfo,
							   Oid **parameterTypes,
							   const char ***parameterValues, bool
							   useOriginalCustomTypeOids)
{
	int parameterIndex = 0;
	int parameterCount = paramListInfo->numParams;

	*parameterTypes = (Oid *) palloc0(parameterCount * sizeof(Oid));
	*parameterValues = (const char **) palloc0(parameterCount * sizeof(char *));

	/* get parameter types and values */
	for (parameterIndex = 0; parameterIndex < parameterCount; parameterIndex++)
	{
		ParamExternData *parameterData = &paramListInfo->params[parameterIndex];
		Oid typeOutputFunctionId = InvalidOid;
		bool variableLengthType = false;

		/*
		 * Use 0 for data types where the oid values can be different on
		 * the master and worker nodes. Therefore, the worker nodes can
		 * infer the correct oid.
		 */
		if (parameterData->ptype >= FirstNormalObjectId && !useOriginalCustomTypeOids)
		{
			(*parameterTypes)[parameterIndex] = 0;
		}
		else
		{
			(*parameterTypes)[parameterIndex] = parameterData->ptype;
		}

		/*
		 * If the parameter is not referenced / used (ptype == 0) and
		 * would otherwise have errored out inside standard_planner()),
		 * don't pass a value to the remote side, and pass text oid to prevent
		 * undetermined data type errors on workers.
		 */
		if (parameterData->ptype == 0)
		{
			(*parameterValues)[parameterIndex] = NULL;
			(*parameterTypes)[parameterIndex] = TEXTOID;

			continue;
		}

		/*
		 * If the parameter is NULL then we preserve its type, but
		 * don't need to evaluate its value.
		 */
		if (parameterData->isnull)
		{
			(*parameterValues)[parameterIndex] = NULL;

			continue;
		}

		getTypeOutputInfo(parameterData->ptype, &typeOutputFunctionId,
						  &variableLengthType);

		(*parameterValues)[parameterIndex] = OidOutputFunctionCall(typeOutputFunctionId,
																   parameterData->value);
	}
}