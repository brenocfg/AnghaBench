#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32 ;
typedef  int /*<<< orphan*/  bytea ;
typedef  TYPE_1__* TupleDesc ;
struct TYPE_17__ {char* null_print_client; char* delim; scalar_t__ binary; int /*<<< orphan*/  rowcontext; } ;
struct TYPE_16__ {scalar_t__ attgenerated; scalar_t__ attisdropped; } ;
struct TYPE_15__ {int /*<<< orphan*/  natts; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_2__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_3__* CopyOutState ;
typedef  int /*<<< orphan*/  CopyCoercionData ;

/* Variables and functions */
 scalar_t__ ATTRIBUTE_GENERATED_STORED ; 
 size_t AvailableColumnCount (TYPE_1__*) ; 
 int /*<<< orphan*/  CoerceColumnValue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CopyAttributeOutText (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  CopySendChar (TYPE_3__*,char) ; 
 int /*<<< orphan*/  CopySendData (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CopySendInt16 (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  CopySendInt32 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  CopySendString (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 char* OutputFunctionCall (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SendFunctionCall (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* TupleDescAttr (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  VARDATA (int /*<<< orphan*/ *) ; 
 int VARHDRSZ ; 
 int VARSIZE (int /*<<< orphan*/ *) ; 

void
AppendCopyRowData(Datum *valueArray, bool *isNullArray, TupleDesc rowDescriptor,
				  CopyOutState rowOutputState, FmgrInfo *columnOutputFunctions,
				  CopyCoercionData *columnCoercionPaths)
{
	uint32 totalColumnCount = (uint32) rowDescriptor->natts;
	uint32 availableColumnCount = AvailableColumnCount(rowDescriptor);
	uint32 appendedColumnCount = 0;
	uint32 columnIndex = 0;

	MemoryContext oldContext = MemoryContextSwitchTo(rowOutputState->rowcontext);

	if (rowOutputState->binary)
	{
		CopySendInt16(rowOutputState, availableColumnCount);
	}
	for (columnIndex = 0; columnIndex < totalColumnCount; columnIndex++)
	{
		Form_pg_attribute currentColumn = TupleDescAttr(rowDescriptor, columnIndex);
		Datum value = valueArray[columnIndex];
		bool isNull = isNullArray[columnIndex];
		bool lastColumn = false;

		if (!isNull && columnCoercionPaths != NULL)
		{
			value = CoerceColumnValue(value, &columnCoercionPaths[columnIndex]);
		}

		if (currentColumn->attisdropped
#if PG_VERSION_NUM >= 120000
			|| currentColumn->attgenerated == ATTRIBUTE_GENERATED_STORED
#endif
			)
		{
			continue;
		}
		else if (rowOutputState->binary)
		{
			if (!isNull)
			{
				FmgrInfo *outputFunctionPointer = &columnOutputFunctions[columnIndex];
				bytea *outputBytes = SendFunctionCall(outputFunctionPointer, value);

				CopySendInt32(rowOutputState, VARSIZE(outputBytes) - VARHDRSZ);
				CopySendData(rowOutputState, VARDATA(outputBytes),
							 VARSIZE(outputBytes) - VARHDRSZ);
			}
			else
			{
				CopySendInt32(rowOutputState, -1);
			}
		}
		else
		{
			if (!isNull)
			{
				FmgrInfo *outputFunctionPointer = &columnOutputFunctions[columnIndex];
				char *columnText = OutputFunctionCall(outputFunctionPointer, value);

				CopyAttributeOutText(rowOutputState, columnText);
			}
			else
			{
				CopySendString(rowOutputState, rowOutputState->null_print_client);
			}

			lastColumn = ((appendedColumnCount + 1) == availableColumnCount);
			if (!lastColumn)
			{
				CopySendChar(rowOutputState, rowOutputState->delim[0]);
			}
		}

		appendedColumnCount++;
	}

	if (!rowOutputState->binary)
	{
		/* append default line termination string depending on the platform */
#ifndef WIN32
		CopySendChar(rowOutputState, '\n');
#else
		CopySendString(rowOutputState, "\r\n");
#endif
	}

	MemoryContextSwitchTo(oldContext);
}