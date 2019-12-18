#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  tupdesc; int /*<<< orphan*/ ** vals; } ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* StringInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  AssertArg (int) ; 
 int /*<<< orphan*/  DatumGetBool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  IsDistributedTable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SELECT_EXIST_QUERY ; 
 int SPI_OK_CONNECT ; 
 int SPI_OK_SELECT ; 
 int SPI_connect () ; 
 int SPI_execute (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_finish () ; 
 int /*<<< orphan*/  SPI_getbinval (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 
 int SPI_processed ; 
 TYPE_4__* SPI_tuptable ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 char* get_namespace_name (int /*<<< orphan*/ ) ; 
 char* get_rel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rel_namespace (int /*<<< orphan*/ ) ; 
 TYPE_1__* makeStringInfo () ; 
 char* quote_qualified_identifier (char*,char*) ; 

__attribute__((used)) static bool
LocalTableEmpty(Oid tableId)
{
	Oid schemaId = get_rel_namespace(tableId);
	char *schemaName = get_namespace_name(schemaId);
	char *tableName = get_rel_name(tableId);
	char *tableQualifiedName = quote_qualified_identifier(schemaName, tableName);

	int spiConnectionResult = 0;
	int spiQueryResult = 0;
	StringInfo selectExistQueryString = makeStringInfo();

	HeapTuple tuple = NULL;
	Datum hasDataDatum = 0;
	bool localTableEmpty = false;
	bool columnNull = false;
	bool readOnly = true;

	int rowId = 0;
	int attributeId = 1;

	AssertArg(!IsDistributedTable(tableId));

	spiConnectionResult = SPI_connect();
	if (spiConnectionResult != SPI_OK_CONNECT)
	{
		ereport(ERROR, (errmsg("could not connect to SPI manager")));
	}

	appendStringInfo(selectExistQueryString, SELECT_EXIST_QUERY, tableQualifiedName);

	spiQueryResult = SPI_execute(selectExistQueryString->data, readOnly, 0);
	if (spiQueryResult != SPI_OK_SELECT)
	{
		ereport(ERROR, (errmsg("execution was not successful \"%s\"",
							   selectExistQueryString->data)));
	}

	/* we expect that SELECT EXISTS query will return single value in a single row */
	Assert(SPI_processed == 1);

	tuple = SPI_tuptable->vals[rowId];
	hasDataDatum = SPI_getbinval(tuple, SPI_tuptable->tupdesc, attributeId, &columnNull);
	localTableEmpty = !DatumGetBool(hasDataDatum);

	SPI_finish();

	return localTableEmpty;
}