#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_7__ {int len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* StringInfo ;
typedef  int /*<<< orphan*/  FileCompat ;
typedef  int /*<<< orphan*/  File ;

/* Variables and functions */
 int /*<<< orphan*/  FileClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FileCompatFromFileStart (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FileOpenForTransmit (char const*,int const,int const) ; 
 int FileReadCompat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeStringInfo (TYPE_1__*) ; 
 int O_RDONLY ; 
 int PG_BINARY ; 
 int /*<<< orphan*/  PG_WAIT_IO ; 
 int /*<<< orphan*/  SendCopyData (TYPE_1__*) ; 
 int /*<<< orphan*/  SendCopyDone () ; 
 int /*<<< orphan*/  SendCopyOutStart () ; 
 int /*<<< orphan*/  enlargeStringInfo (TYPE_1__*,int const) ; 
 TYPE_1__* makeStringInfo () ; 
 int /*<<< orphan*/  resetStringInfo (TYPE_1__*) ; 

void
SendRegularFile(const char *filename)
{
	StringInfo fileBuffer = NULL;
	int readBytes = -1;
	const uint32 fileBufferSize = 32768; /* 32 KB */
	const int fileFlags = (O_RDONLY | PG_BINARY);
	const int fileMode = 0;

	/* we currently do not check if the caller has permissions for this file */
	File fileDesc = FileOpenForTransmit(filename, fileFlags, fileMode);
	FileCompat fileCompat = FileCompatFromFileStart(fileDesc);

	/*
	 * We read file's contents into buffers of 32 KB. This buffer size is twice
	 * as large as Hadoop's default buffer size, and may later be configurable.
	 */
	fileBuffer = makeStringInfo();
	enlargeStringInfo(fileBuffer, fileBufferSize);

	SendCopyOutStart();

	readBytes = FileReadCompat(&fileCompat, fileBuffer->data, fileBufferSize,
							   PG_WAIT_IO);
	while (readBytes > 0)
	{
		fileBuffer->len = readBytes;

		SendCopyData(fileBuffer);

		resetStringInfo(fileBuffer);
		readBytes = FileReadCompat(&fileCompat, fileBuffer->data, fileBufferSize,
								   PG_WAIT_IO);
	}

	SendCopyDone();

	FreeStringInfo(fileBuffer);
	FileClose(fileDesc);
}