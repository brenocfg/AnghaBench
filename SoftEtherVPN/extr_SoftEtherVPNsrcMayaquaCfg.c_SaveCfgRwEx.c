#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_5__ {int DontBackup; int /*<<< orphan*/  lock; int /*<<< orphan*/  FileNameW; int /*<<< orphan*/ * Io; } ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_1__ CFG_RW ;

/* Variables and functions */
 int /*<<< orphan*/  BackupCfgWEx (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ CfgSaveExW2 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  FileClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * FileOpenW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

UINT SaveCfgRwEx(CFG_RW *rw, FOLDER *f, UINT revision_number)
{
	UINT ret = 0;
	// Validate arguments
	if (rw == NULL || f == NULL)
	{
		return 0;
	}

	Lock(rw->lock);
	{
		if (rw->Io != NULL)
		{
			FileClose(rw->Io);
			rw->Io = NULL;
		}

		if (CfgSaveExW2(rw, f, rw->FileNameW, &ret))
		{
			if (rw->DontBackup == false)
			{
				BackupCfgWEx(rw, f, rw->FileNameW, revision_number);
			}
		}
		else
		{
			ret = 0;
		}

		rw->Io = FileOpenW(rw->FileNameW, false);
	}
	Unlock(rw->lock);

	return ret;
}