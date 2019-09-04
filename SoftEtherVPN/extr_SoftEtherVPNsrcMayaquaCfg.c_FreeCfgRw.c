#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* FileName; struct TYPE_4__* FileNameW; int /*<<< orphan*/  lock; int /*<<< orphan*/ * Io; } ;
typedef  TYPE_1__ CFG_RW ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FileClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 

void FreeCfgRw(CFG_RW *rw)
{
	// Validate arguments
	if (rw == NULL)
	{
		return;
	}

	if (rw->Io != NULL)
	{
		FileClose(rw->Io);
	}

	DeleteLock(rw->lock);
	Free(rw->FileNameW);
	Free(rw->FileName);
	Free(rw);
}