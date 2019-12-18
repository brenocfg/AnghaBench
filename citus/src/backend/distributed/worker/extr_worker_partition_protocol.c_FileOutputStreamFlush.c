#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* filePath; int /*<<< orphan*/  fileCompat; TYPE_2__* fileBuffer; } ;
struct TYPE_6__ {int len; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__* StringInfo ;
typedef  TYPE_3__ FileOutputStream ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int FileWriteCompat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_WAIT_IO ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 

__attribute__((used)) static void
FileOutputStreamFlush(FileOutputStream *file)
{
	StringInfo fileBuffer = file->fileBuffer;
	int written = 0;

	errno = 0;
	written = FileWriteCompat(&file->fileCompat, fileBuffer->data, fileBuffer->len,
							  PG_WAIT_IO);
	if (written != fileBuffer->len)
	{
		ereport(ERROR, (errcode_for_file_access(),
						errmsg("could not write %d bytes to partition file \"%s\"",
							   fileBuffer->len, file->filePath->data)));
	}
}