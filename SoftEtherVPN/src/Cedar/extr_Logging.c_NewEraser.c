#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dir ;
typedef  scalar_t__ UINT64 ;
struct TYPE_7__ {int /*<<< orphan*/  OsType; } ;
struct TYPE_6__ {int /*<<< orphan*/  Thread; int /*<<< orphan*/  HaltEvent; int /*<<< orphan*/  DirName; scalar_t__ MinFreeSpace; int /*<<< orphan*/ * Log; } ;
typedef  int /*<<< orphan*/  LOG ;
typedef  TYPE_1__ ERASER ;

/* Variables and functions */
 int /*<<< orphan*/  CopyStr (char*) ; 
 scalar_t__ DISK_FREE_SPACE_DEFAULT ; 
 scalar_t__ DISK_FREE_SPACE_DEFAULT_WINDOWS ; 
 scalar_t__ DISK_FREE_SPACE_MIN ; 
 int /*<<< orphan*/  EraserThread ; 
 int /*<<< orphan*/  GetExeDir (char*,int) ; 
 TYPE_5__* GetOsInfo () ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  NewEvent () ; 
 int /*<<< orphan*/  NewThread (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ OS_IS_WINDOWS (int /*<<< orphan*/ ) ; 
 TYPE_1__* ZeroMalloc (int) ; 

ERASER *NewEraser(LOG *log, UINT64 min_size)
{
	ERASER *e;
	char dir[MAX_PATH];

	if (min_size == 0)
	{
		if (OS_IS_WINDOWS(GetOsInfo()->OsType))
		{
			min_size = DISK_FREE_SPACE_DEFAULT_WINDOWS;
		}
		else
		{
			min_size = DISK_FREE_SPACE_DEFAULT;
		}
	}

	if (min_size < DISK_FREE_SPACE_MIN)
	{
		min_size = DISK_FREE_SPACE_MIN;
	}

	e = ZeroMalloc(sizeof(ERASER));

	GetExeDir(dir, sizeof(dir));

	e->Log = log;
	e->MinFreeSpace = min_size;
	e->DirName = CopyStr(dir);
	e->HaltEvent = NewEvent();

	e->Thread = NewThread(EraserThread, e);

	return e;
}