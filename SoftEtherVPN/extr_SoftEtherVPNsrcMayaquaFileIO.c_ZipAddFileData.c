#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* CurrentFile; int /*<<< orphan*/  Fifo; } ;
typedef  TYPE_2__ ZIP_PACKER ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_5__ {scalar_t__ CurrentSize; scalar_t__ Size; int /*<<< orphan*/  Crc32; } ;

/* Variables and functions */
 int /*<<< orphan*/  Crc32Next (void*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteFifo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ZipAddFileFooter (TYPE_2__*) ; 

UINT ZipAddFileData(ZIP_PACKER *p, void *data, UINT pos, UINT len)
{
	UINT ret;
	UINT total_size;
	// Validate arguments
	if (p == NULL)
	{
		return 0;
	}

	total_size = p->CurrentFile->CurrentSize + len;

	if (total_size > p->CurrentFile->Size)
	{
		return 0;
	}

	WriteFifo(p->Fifo, ((UCHAR *)data) + pos, len);

	p->CurrentFile->CurrentSize += len;
	p->CurrentFile->Crc32 = Crc32Next(data, pos, len, p->CurrentFile->Crc32);

	ret = p->CurrentFile->Size - p->CurrentFile->CurrentSize;

	if (ret == 0)
	{
		p->CurrentFile->Crc32 = ~p->CurrentFile->Crc32;

		ZipAddFileFooter(p);

		p->CurrentFile = NULL;
	}

	return ret;
}