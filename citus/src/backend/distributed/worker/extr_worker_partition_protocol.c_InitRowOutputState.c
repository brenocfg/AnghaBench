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
struct TYPE_3__ {char* null_print; char* null_print_client; int file_encoding; int need_transcoding; int /*<<< orphan*/  fe_msgbuf; int /*<<< orphan*/  rowcontext; int /*<<< orphan*/  binary; void* delim; } ;
typedef  int /*<<< orphan*/  CopyOutStateData ;
typedef  TYPE_1__* CopyOutState ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_INITSIZE ; 
 int /*<<< orphan*/  ALLOCSET_DEFAULT_MAXSIZE ; 
 int /*<<< orphan*/  ALLOCSET_DEFAULT_MINSIZE ; 
 int /*<<< orphan*/  AllocSetContextCreateExtended (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BinaryWorkerCopyFormat ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  ERROR ; 
 int GetDatabaseEncoding () ; 
 scalar_t__ PG_ENCODING_IS_CLIENT_ONLY (int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  makeStringInfo () ; 
 int /*<<< orphan*/  palloc0 (int) ; 
 int pg_database_encoding_max_length () ; 
 int pg_get_client_encoding () ; 
 char* pg_server_to_any (char*,int,int) ; 
 void* pstrdup (char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static CopyOutState
InitRowOutputState(void)
{
	CopyOutState rowOutputState = (CopyOutState) palloc0(sizeof(CopyOutStateData));

	int fileEncoding = pg_get_client_encoding();
	int databaseEncoding = GetDatabaseEncoding();
	int databaseEncodingMaxLength = pg_database_encoding_max_length();

	/* initialize defaults for printing null values */
	char *nullPrint = pstrdup("\\N");
	int nullPrintLen = strlen(nullPrint);
	char *nullPrintClient = pg_server_to_any(nullPrint, nullPrintLen, fileEncoding);

	/* set default text output characters */
	rowOutputState->null_print = nullPrint;
	rowOutputState->null_print_client = nullPrintClient;
	rowOutputState->delim = pstrdup("\t");

	rowOutputState->binary = BinaryWorkerCopyFormat;

	/* set encoding conversion information */
	rowOutputState->file_encoding = fileEncoding;

	if (PG_ENCODING_IS_CLIENT_ONLY(fileEncoding))
	{
		ereport(ERROR, (errmsg("cannot repartition into encoding caller cannot "
							   "receive")));
	}

	/* set up transcoding information and default text output characters */
	if ((fileEncoding != databaseEncoding) || (databaseEncodingMaxLength > 1))
	{
		rowOutputState->need_transcoding = true;
	}
	else
	{
		rowOutputState->need_transcoding = false;
	}

	/*
	 * Create a temporary memory context that we can reset once per row to
	 * recover palloc'd memory. This avoids any problems with leaks inside data
	 * type output routines, and should be faster than retail pfree's anyway.
	 */
	rowOutputState->rowcontext = AllocSetContextCreateExtended(CurrentMemoryContext,
															   "WorkerRowOutputContext",
															   ALLOCSET_DEFAULT_MINSIZE,
															   ALLOCSET_DEFAULT_INITSIZE,
															   ALLOCSET_DEFAULT_MAXSIZE);

	/* allocate the message buffer to use for serializing a row */
	rowOutputState->fe_msgbuf = makeStringInfo();

	return rowOutputState;
}