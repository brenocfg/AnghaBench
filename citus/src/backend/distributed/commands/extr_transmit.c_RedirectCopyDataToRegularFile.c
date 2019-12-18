#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* StringInfo ;
typedef  int /*<<< orphan*/  FileCompat ;
typedef  int /*<<< orphan*/  File ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FileClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FileCompatFromFileStart (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FileOpenForTransmit (char const*,int const,int const) ; 
 int FileWriteCompat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeStringInfo (TYPE_1__*) ; 
 int O_APPEND ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int PG_BINARY ; 
 int /*<<< orphan*/  PG_WAIT_IO ; 
 int ReceiveCopyData (TYPE_1__*) ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  SendCopyInStart () ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 TYPE_1__* makeStringInfo () ; 
 int /*<<< orphan*/  resetStringInfo (TYPE_1__*) ; 

void
RedirectCopyDataToRegularFile(const char *filename)
{
	StringInfo copyData = makeStringInfo();
	bool copyDone = false;
	const int fileFlags = (O_APPEND | O_CREAT | O_RDWR | O_TRUNC | PG_BINARY);
	const int fileMode = (S_IRUSR | S_IWUSR);
	File fileDesc = FileOpenForTransmit(filename, fileFlags, fileMode);
	FileCompat fileCompat = FileCompatFromFileStart(fileDesc);

	SendCopyInStart();

	copyDone = ReceiveCopyData(copyData);
	while (!copyDone)
	{
		/* if received data has contents, append to regular file */
		if (copyData->len > 0)
		{
			int appended = FileWriteCompat(&fileCompat, copyData->data,
										   copyData->len, PG_WAIT_IO);

			if (appended != copyData->len)
			{
				ereport(ERROR, (errcode_for_file_access(),
								errmsg("could not append to received file: %m")));
			}
		}

		resetStringInfo(copyData);
		copyDone = ReceiveCopyData(copyData);
	}

	FreeStringInfo(copyData);
	FileClose(fileDesc);
}