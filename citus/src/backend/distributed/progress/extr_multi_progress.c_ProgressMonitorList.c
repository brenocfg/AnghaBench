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
typedef  scalar_t__ uint64 ;
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  dsm_segment ;
typedef  void* dsm_handle ;
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_3__ {int /*<<< orphan*/  setResult; int /*<<< orphan*/  setDesc; } ;
typedef  TYPE_1__ ReturnSetInfo ;
typedef  int /*<<< orphan*/  ProgressMonitorData ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 void* DatumGetUInt64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecClearTuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecDropSingleTupleTableSlot (int /*<<< orphan*/ *) ; 
 TYPE_1__* FunctionCallGetTupleStore1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionOid (char*,char*,int) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/ * MakeSingleTupleTableSlotCompat (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * MonitorDataFromDSMHandle (void*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TTSOpsMinimalTuple ; 
 int /*<<< orphan*/ * cstring_to_text (char*) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_stat_get_progress_info ; 
 int /*<<< orphan*/  slot_getattr (int /*<<< orphan*/ *,int const,int*) ; 
 int tuplestore_gettupleslot (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

List *
ProgressMonitorList(uint64 commandTypeMagicNumber, List **attachedDSMSegments)
{
	/*
	 * The expected magic number should reside in the first progress field and the
	 * actual segment handle in the second but the slot ordering is 1-indexed in the
	 * tuple table slot and there are 3 other fields before the progress fields in the
	 * pg_stat_get_progress_info output.
	 */
	const int magicNumberIndex = 0 + 1 + 3;
	const int dsmHandleIndex = 1 + 1 + 3;

	/*
	 * Currently, Postgres' progress logging mechanism supports only the VACUUM
	 * operations. Therefore, we identify ourselves as a VACUUM command but only fill
	 * a couple of the available fields. Therefore the commands that use Citus' progress
	 * monitoring API will appear in pg_stat_progress_vacuum output.
	 */
	text *commandTypeText = cstring_to_text("VACUUM");
	Datum commandTypeDatum = PointerGetDatum(commandTypeText);
	Oid getProgressInfoFunctionOid = InvalidOid;
	TupleTableSlot *tupleTableSlot = NULL;
	ReturnSetInfo *progressResultSet = NULL;
	List *monitorList = NIL;

	getProgressInfoFunctionOid = FunctionOid("pg_catalog",
											 "pg_stat_get_progress_info",
											 1);

	progressResultSet = FunctionCallGetTupleStore1(pg_stat_get_progress_info,
												   getProgressInfoFunctionOid,
												   commandTypeDatum);

	tupleTableSlot = MakeSingleTupleTableSlotCompat(progressResultSet->setDesc,
													&TTSOpsMinimalTuple);

	/* iterate over tuples in tuple store, and send them to destination */
	for (;;)
	{
		bool nextTuple = false;
		bool isNull = false;
		Datum magicNumberDatum = 0;
		uint64 magicNumber = 0;

		nextTuple = tuplestore_gettupleslot(progressResultSet->setResult,
											true,
											false,
											tupleTableSlot);

		if (!nextTuple)
		{
			break;
		}

		magicNumberDatum = slot_getattr(tupleTableSlot, magicNumberIndex, &isNull);
		magicNumber = DatumGetUInt64(magicNumberDatum);

		if (!isNull && magicNumber == commandTypeMagicNumber)
		{
			Datum dsmHandleDatum = slot_getattr(tupleTableSlot, dsmHandleIndex, &isNull);
			dsm_handle dsmHandle = DatumGetUInt64(dsmHandleDatum);
			dsm_segment *attachedSegment = NULL;
			ProgressMonitorData *monitor = MonitorDataFromDSMHandle(dsmHandle,
																	&attachedSegment);

			if (monitor != NULL)
			{
				*attachedDSMSegments = lappend(*attachedDSMSegments, attachedSegment);
				monitorList = lappend(monitorList, monitor);
			}
		}

		ExecClearTuple(tupleTableSlot);
	}

	ExecDropSingleTupleTableSlot(tupleTableSlot);

	return monitorList;
}