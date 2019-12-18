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
struct TYPE_3__ {int coercionType; int /*<<< orphan*/  coerceFunction; int /*<<< orphan*/  inputFunction; int /*<<< orphan*/  typioparam; int /*<<< orphan*/  outputFunction; } ;
typedef  scalar_t__ Oid ;
typedef  TYPE_1__ CopyCoercionData ;
typedef  int CoercionPathType ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  COERCION_EXPLICIT ; 
#define  COERCION_PATH_ARRAYCOERCE 132 
#define  COERCION_PATH_COERCEVIAIO 131 
#define  COERCION_PATH_FUNC 130 
#define  COERCION_PATH_NONE 129 
#define  COERCION_PATH_RELABELTYPE 128 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int find_coercion_pathway (scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  fmgr_info (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getTypeInputInfo (scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getTypeOutputInfo (scalar_t__,scalar_t__*,int*) ; 
 scalar_t__ get_base_element_type (scalar_t__) ; 

void
ConversionPathForTypes(Oid inputType, Oid destType, CopyCoercionData *result)
{
	Oid coercionFuncId = InvalidOid;
	CoercionPathType coercionType = COERCION_PATH_RELABELTYPE;

	if (destType == inputType)
	{
		result->coercionType = COERCION_PATH_RELABELTYPE;
		return;
	}

	coercionType = find_coercion_pathway(destType, inputType,
										 COERCION_EXPLICIT,
										 &coercionFuncId);

	switch (coercionType)
	{
		case COERCION_PATH_NONE:
		{
			ereport(ERROR, (errmsg("cannot cast %d to %d", inputType, destType)));
			return;
		}

		case COERCION_PATH_ARRAYCOERCE:
		{
			Oid inputBaseType = get_base_element_type(inputType);
			Oid destBaseType = get_base_element_type(destType);
			CoercionPathType baseCoercionType = COERCION_PATH_NONE;

			if (inputBaseType != InvalidOid && destBaseType != InvalidOid)
			{
				baseCoercionType = find_coercion_pathway(inputBaseType, destBaseType,
														 COERCION_EXPLICIT,
														 &coercionFuncId);
			}

			if (baseCoercionType != COERCION_PATH_COERCEVIAIO)
			{
				ereport(ERROR, (errmsg("can not run query which uses an implicit coercion"
									   " between array types")));
			}
		}

		/* fallthrough */

		case COERCION_PATH_COERCEVIAIO:
		{
			result->coercionType = COERCION_PATH_COERCEVIAIO;

			{
				bool typisvarlena = false; /* ignored */
				Oid iofunc = InvalidOid;
				getTypeOutputInfo(inputType, &iofunc, &typisvarlena);
				fmgr_info(iofunc, &(result->outputFunction));
			}

			{
				Oid iofunc = InvalidOid;
				getTypeInputInfo(destType, &iofunc, &(result->typioparam));
				fmgr_info(iofunc, &(result->inputFunction));
			}

			return;
		}

		case COERCION_PATH_FUNC:
		{
			result->coercionType = COERCION_PATH_FUNC;
			fmgr_info(coercionFuncId, &(result->coerceFunction));
			return;
		}

		case COERCION_PATH_RELABELTYPE:
		{
			result->coercionType = COERCION_PATH_RELABELTYPE;
			return; /* the types are binary compatible, no need to call a function */
		}

		default:
			Assert(false); /* there are no other options for this enum */
	}
}