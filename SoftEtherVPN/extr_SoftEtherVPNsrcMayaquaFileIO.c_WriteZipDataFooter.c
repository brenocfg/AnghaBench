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
struct TYPE_5__ {int Size; int Crc32; } ;
typedef  TYPE_1__ ZIP_FILE ;
struct TYPE_6__ {void* Crc32; void* UncompSize; void* CompSize; void* Signature; } ;
typedef  TYPE_2__ ZIP_DATA_FOOTER ;

/* Variables and functions */
 void* Endian32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Swap32 (int) ; 

void WriteZipDataFooter(ZIP_FILE *f, ZIP_DATA_FOOTER *h)
{
	// Validate arguments
	if (f == NULL || h ==NULL)
	{
		return;
	}

	h->Signature = Endian32(Swap32(0x08074B50));
	h->CompSize = h->UncompSize = Endian32(Swap32(f->Size));
	h->Crc32 = Endian32(Swap32(f->Crc32));
}