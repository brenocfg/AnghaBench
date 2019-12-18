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
typedef  int /*<<< orphan*/  f ;
struct TYPE_3__ {int /*<<< orphan*/  Fifo; int /*<<< orphan*/  CurrentFile; } ;
typedef  TYPE_1__ ZIP_PACKER ;
typedef  int /*<<< orphan*/  ZIP_DATA_FOOTER ;

/* Variables and functions */
 int /*<<< orphan*/  WriteFifo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WriteZipDataFooter (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

void ZipAddFileFooter(ZIP_PACKER *p)
{
	ZIP_DATA_FOOTER f;
	// Validate arguments
	if (p == NULL)
	{
		return;
	}

	Zero(&f, sizeof(f));
	WriteZipDataFooter(p->CurrentFile, &f);

	WriteFifo(p->Fifo, &f, sizeof(f));
}