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
struct TYPE_5__ {int /*<<< orphan*/  Name; int /*<<< orphan*/  Crc32; int /*<<< orphan*/  Size; int /*<<< orphan*/  DateTime; } ;
typedef  TYPE_1__ ZIP_FILE ;
struct TYPE_6__ {scalar_t__ ExtraLen; void* FileNameLen; void* Crc32; void* UncompSize; void* CompSize; void* Option; void* FileTime; void* FileDate; scalar_t__ CompType; void* NeedVer; void* Signature; } ;
typedef  TYPE_2__ ZIP_DATA_HEADER ;

/* Variables and functions */
 void* Endian16 (int /*<<< orphan*/ ) ; 
 void* Endian32 (int /*<<< orphan*/ ) ; 
 int StrLen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Swap16 (int) ; 
 int /*<<< orphan*/  Swap32 (int /*<<< orphan*/ ) ; 
 int System64ToDosDate (int /*<<< orphan*/ ) ; 
 int System64ToDosTime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZIP_SIGNATURE ; 
 int ZIP_VERSION ; 

void WriteZipDataHeader(ZIP_FILE *f, ZIP_DATA_HEADER *h, bool write_sizes)
{
	// Validate arguments
	if (f == NULL || h ==NULL)
	{
		return;
	}

	h->Signature = Endian32(Swap32(ZIP_SIGNATURE));
	h->NeedVer = Endian16(Swap16(ZIP_VERSION));
	h->CompType = 0;
	h->FileDate = Endian16(Swap16(System64ToDosDate(f->DateTime)));
	h->FileTime = Endian16(Swap16(System64ToDosTime(f->DateTime)));
	h->Option = Endian16(Swap16(8)); // bit3: Set the file-size and the CRC in local header to 0

	if (write_sizes == false)
	{
		h->CompSize = h->UncompSize = 0;
		h->Crc32 = 0;
	}
	else
	{
		h->CompSize = h->UncompSize = Endian32(Swap32(f->Size));
		h->Crc32 = Endian32(Swap32(f->Crc32));
	}

	h->FileNameLen = Endian16(Swap16(StrLen(f->Name)));
	h->ExtraLen = 0;
}