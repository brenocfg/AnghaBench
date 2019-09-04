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
struct TYPE_6__ {int /*<<< orphan*/  FileList; int /*<<< orphan*/  Fifo; } ;
typedef  TYPE_1__ ZIP_PACKER ;
typedef  TYPE_1__ ZIP_FILE ;
typedef  scalar_t__ UINT ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseFifo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ ) ; 

void FreeZipPacker(ZIP_PACKER *p)
{
	UINT i;
	// Validate arguments
	if (p == NULL)
	{
		return;
	}

	ReleaseFifo(p->Fifo);

	for (i = 0;i < LIST_NUM(p->FileList);i++)
	{
		ZIP_FILE *f = LIST_DATA(p->FileList, i);

		Free(f);
	}

	ReleaseList(p->FileList);

	Free(p);
}