#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32 ;
struct TYPE_6__ {int /*<<< orphan*/  fd; } ;
struct TYPE_7__ {int /*<<< orphan*/  filePath; int /*<<< orphan*/  fileBuffer; TYPE_1__ fileCompat; } ;
typedef  TYPE_2__ FileOutputStream ;

/* Variables and functions */
 int /*<<< orphan*/  FileClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FileOutputStreamFlush (TYPE_2__*) ; 
 int /*<<< orphan*/  FreeStringInfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (TYPE_2__*) ; 

__attribute__((used)) static void
ClosePartitionFiles(FileOutputStream *partitionFileArray, uint32 fileCount)
{
	uint32 fileIndex = 0;
	for (fileIndex = 0; fileIndex < fileCount; fileIndex++)
	{
		FileOutputStream *partitionFile = &partitionFileArray[fileIndex];

		FileOutputStreamFlush(partitionFile);

		FileClose(partitionFile->fileCompat.fd);
		FreeStringInfo(partitionFile->fileBuffer);
		FreeStringInfo(partitionFile->filePath);
	}

	pfree(partitionFileArray);
}