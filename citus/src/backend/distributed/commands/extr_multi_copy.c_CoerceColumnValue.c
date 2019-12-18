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
struct TYPE_3__ {int coercionType; int /*<<< orphan*/  typioparam; int /*<<< orphan*/  inputFunction; int /*<<< orphan*/  outputFunction; int /*<<< orphan*/  coerceFunction; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_1__ CopyCoercionData ;

/* Variables and functions */
#define  COERCION_PATH_COERCEVIAIO 130 
#define  COERCION_PATH_FUNC 129 
#define  COERCION_PATH_RELABELTYPE 128 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FunctionCall1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int32GetDatum (int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

Datum
CoerceColumnValue(Datum inputValue, CopyCoercionData *coercionPath)
{
	switch (coercionPath->coercionType)
	{
		case 0:
		{
			return inputValue; /* this was a dropped column */
		}

		case COERCION_PATH_RELABELTYPE:
		{
			return inputValue; /* no need to do anything */
		}

		case COERCION_PATH_FUNC:
		{
			FmgrInfo *coerceFunction = &(coercionPath->coerceFunction);
			Datum outputValue = FunctionCall1(coerceFunction, inputValue);
			return outputValue;
		}

		case COERCION_PATH_COERCEVIAIO:
		{
			FmgrInfo *outFunction = &(coercionPath->outputFunction);
			Datum textRepr = FunctionCall1(outFunction, inputValue);

			FmgrInfo *inFunction = &(coercionPath->inputFunction);
			Oid typioparam = coercionPath->typioparam;
			Datum outputValue = FunctionCall3(inFunction, textRepr, typioparam,
											  Int32GetDatum(-1));

			return outputValue;
		}

		default:
		{
			/* this should never happen */
			ereport(ERROR, (errmsg("unsupported coercion type")));
		}
	}
}