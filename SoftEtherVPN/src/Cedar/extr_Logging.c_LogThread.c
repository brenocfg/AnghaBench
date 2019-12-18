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
typedef  int /*<<< orphan*/  current_logfile_datename ;
typedef  int /*<<< orphan*/  current_file_name ;
typedef  int /*<<< orphan*/  UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_7__ {scalar_t__ num_item; } ;
struct TYPE_6__ {int /*<<< orphan*/  Event; TYPE_2__* RecordQueue; scalar_t__ Halt; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_1__ LOG ;
typedef  int /*<<< orphan*/  IO ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  FileCloseEx (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetIO4Stdout () ; 
 int /*<<< orphan*/  LockQueue (TYPE_2__*) ; 
 int /*<<< orphan*/  LogThreadWriteGeneral (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*,char*,char*) ; 
 int /*<<< orphan*/  LogThreadWriteStdout (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  MsSetThreadPriorityIdle () ; 
 int /*<<< orphan*/  MsSetThreadPriorityRealtime () ; 
 int /*<<< orphan*/ * NewBuf () ; 
 int /*<<< orphan*/  NoticeThreadInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tick64 () ; 
 int /*<<< orphan*/  UnlockQueue (TYPE_2__*) ; 
 int /*<<< orphan*/  Wait (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (char*,int) ; 
 scalar_t__ g_foreground ; 

void LogThread(THREAD *thread, void *param)
{
	LOG *g;
	IO *io;
	BUF *b;
	bool flag = false;
	char current_file_name[MAX_SIZE];
	char current_logfile_datename[MAX_SIZE];
	bool log_date_changed = false;
	// Validate arguments
	if (thread == NULL || param == NULL)
	{
		return;
	}

	Zero(current_file_name, sizeof(current_file_name));
	Zero(current_logfile_datename, sizeof(current_logfile_datename));

	g = (LOG *)param;

	io = g_foreground ? GetIO4Stdout() : NULL;
	b = NewBuf();

#ifdef	OS_WIN32

	// Lower priority to bottom
	MsSetThreadPriorityIdle();

#endif	// OS_WIN32

	NoticeThreadInit(thread);

	while (true)
	{
		UINT64 s = Tick64();

		while (true)
		{
			if (g_foreground)
			{
				if (! LogThreadWriteStdout(g, b, io))
				{
					break;
				}
			}
			else
			{
				if (! LogThreadWriteGeneral(g, b, &io, &log_date_changed, current_logfile_datename, current_file_name))
				{
					break;
				}
			}
		}

		if (g->Halt)
		{
			// Break after finishing to save all records
			// when the stop flag stood
			UINT num;

			if (flag == false)
			{
#ifdef	OS_WIN32
				MsSetThreadPriorityRealtime();
#endif	// OS_WIN32
				flag = true;
			}

			LockQueue(g->RecordQueue);
			{
				num = g->RecordQueue->num_item;
			}
			UnlockQueue(g->RecordQueue);

			if (num == 0 || io == NULL)
			{
				break;
			}
		}
		else
		{
			Wait(g->Event, 9821);
		}
	}

	if (io != NULL && !g_foreground)
	{
		FileCloseEx(io, true);
	}

	FreeBuf(b);
}