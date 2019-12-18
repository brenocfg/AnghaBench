#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32 ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_6__ {int /*<<< orphan*/ * vals; int /*<<< orphan*/  tupdesc; } ;
struct TYPE_5__ {int query_host_port; int /*<<< orphan*/  query_host_name; } ;
typedef  int /*<<< orphan*/ * MemoryContext ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_1__ CitusDistStat ;

/* Variables and functions */
 int /*<<< orphan*/ * CurrentMemoryContext ; 
 TYPE_1__* HeapTupleToCitusDistStat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * MemoryContextSwitchTo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NIL ; 
 int SPI_OK_CONNECT ; 
 int SPI_OK_SELECT ; 
 int SPI_connect () ; 
 int /*<<< orphan*/ * SPI_copytuple (int /*<<< orphan*/ ) ; 
 int SPI_execute (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_finish () ; 
 size_t SPI_processed ; 
 TYPE_3__* SPI_tuptable ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  cstring_to_text (char const*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static List *
LocalNodeCitusDistStat(const char *statQuery, const char *hostname, int port)
{
	List *localNodeCitusDistStatList = NIL;
	int spiConnectionResult = 0;
	int spiQueryResult = 0;
	bool readOnly = true;
	uint32 rowIndex = 0;

	MemoryContext upperContext = CurrentMemoryContext, oldContext = NULL;

	spiConnectionResult = SPI_connect();
	if (spiConnectionResult != SPI_OK_CONNECT)
	{
		ereport(WARNING, (errmsg("could not connect to SPI manager to get "
								 "the local stat activity")));

		SPI_finish();

		return NIL;
	}

	spiQueryResult = SPI_execute(statQuery, readOnly, 0);
	if (spiQueryResult != SPI_OK_SELECT)
	{
		ereport(WARNING, (errmsg("execution was not successful while trying to get "
								 "the local stat activity")));

		SPI_finish();

		return NIL;
	}

	/*
	 * SPI_connect switches to its own memory context, which is destroyed by
	 * the call to SPI_finish. SPI_palloc is provided to allocate memory in
	 * the previous ("upper") context, but that is inadequate when we need to
	 * call other functions that themselves use the normal palloc (such as
	 * lappend). So we switch to the upper context ourselves as needed.
	 */
	oldContext = MemoryContextSwitchTo(upperContext);

	for (rowIndex = 0; rowIndex < SPI_processed; rowIndex++)
	{
		HeapTuple row = NULL;
		TupleDesc rowDescriptor = SPI_tuptable->tupdesc;
		CitusDistStat *citusDistStat = NULL;

		/* we use pointers from the tuple, so copy it before processing */
		row = SPI_copytuple(SPI_tuptable->vals[rowIndex]);
		citusDistStat = HeapTupleToCitusDistStat(row, rowDescriptor);

		/*
		 * Add the query_host_name and query_host_port which denote where
		 * the query is being running.
		 */
		citusDistStat->query_host_name = cstring_to_text(hostname);
		citusDistStat->query_host_port = port;

		localNodeCitusDistStatList = lappend(localNodeCitusDistStatList, citusDistStat);
	}

	MemoryContextSwitchTo(oldContext);

	SPI_finish();

	return localNodeCitusDistStatList;
}