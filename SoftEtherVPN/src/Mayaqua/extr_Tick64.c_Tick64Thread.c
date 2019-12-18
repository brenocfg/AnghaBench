#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {scalar_t__ LastTick; scalar_t__ TickStart; scalar_t__ Tick; scalar_t__ Tick64WithTime64; scalar_t__ Time64; scalar_t__ Halt; int /*<<< orphan*/  AdjustTime; int /*<<< orphan*/  TickLock; scalar_t__ RoundCount; } ;
struct TYPE_8__ {scalar_t__ Time; scalar_t__ Tick; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_1__ ADJUST_TIME ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Debug (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ Diff64 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ ,int) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 scalar_t__ MAX_ADJUST_TIME ; 
 int /*<<< orphan*/  MsSetThreadPriorityRealtime () ; 
 int /*<<< orphan*/  NoticeThreadInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SleepThread (scalar_t__) ; 
 void* SystemTime64 () ; 
 scalar_t__ TICK64_SPAN ; 
 scalar_t__ TICK64_SPAN_WIN32 ; 
 scalar_t__ TickRealtime () ; 
 int /*<<< orphan*/  UnixSetThreadPriorityRealtime () ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Wait (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ Win32FastTick64 () ; 
 TYPE_1__* ZeroMalloc (int) ; 
 int /*<<< orphan*/  halt_tick_event ; 
 TYPE_2__* tk64 ; 

void Tick64Thread(THREAD *thread, void *param)
{
	UINT n = 0;
	bool first = false;
	bool create_first_entry = true;
	UINT tick_span;
	// Validate arguments
	if (thread == NULL)
	{
		return;
	}

#ifdef	OS_WIN32

	// Raise the priority of the Win32 thread
	MsSetThreadPriorityRealtime();

	tick_span = TICK64_SPAN_WIN32;

#else	// OS_WIN32

	// Raise the priority of a POSIX threads
	UnixSetThreadPriorityRealtime();

	tick_span = TICK64_SPAN;

#endif	// OS_WIN32

	while (true)
	{
		UINT tick;
		UINT64 tick64;

#ifndef	OS_WIN32
		tick = TickRealtime();		// Get the current system clock

		if (tk64->LastTick > tick)
		{
			if ((tk64->LastTick - tick) >= (UINT64)0x0fffffff)
			{
				// The Tick has gone lap around
				tk64->RoundCount++;
			}
			else
			{
				// tick skewed (System administrator might change hardware clock)
				// Normally, the clock skew appears as sub-seconds error
				tick = tk64->LastTick;
			}
		}
		tk64->LastTick = tick;

		tick64 = (UINT64)tk64->RoundCount * (UINT64)4294967296LL + (UINT64)tick;

		Lock(tk64->TickLock);
		{
			if (tk64->TickStart == 0)
			{
				tk64->TickStart = tick64;
			}
			tick64 = tk64->Tick = tick64 - tk64->TickStart + (UINT64)1;
		}
		Unlock(tk64->TickLock);
#else	// OS_WIN32
		tick64 = Win32FastTick64();
		tick = (UINT)tick64;
#endif	// OS_WIN32

		if (create_first_entry)
		{
			ADJUST_TIME *t = ZeroMalloc(sizeof(ADJUST_TIME));
			t->Tick = tick64;
			t->Time = SystemTime64();
			tk64->Tick64WithTime64 = tick64;
			tk64->Time64 = t->Time;
			Add(tk64->AdjustTime, t);

			// Notify the completion of the initialization 
			NoticeThreadInit(thread);
			create_first_entry = false;
		}

		// Time correction
		n += tick_span;
		if (n >= 1000 || first == false)
		{
			UINT64 now = SystemTime64();

			if (now < tk64->Time64 ||
				Diff64((now - tk64->Time64) + tk64->Tick64WithTime64, tick64) >= tick_span)
			{
				ADJUST_TIME *t = ZeroMalloc(sizeof(ADJUST_TIME));
				LockList(tk64->AdjustTime);
				{
					t->Tick = tick64;
					t->Time = now;
					Add(tk64->AdjustTime, t);
					Debug("Adjust Time: Tick = %I64u, Time = %I64u\n",
						t->Tick, t->Time);

					// To prevent consuming memory infinite on a system that clock is skewd
					if (LIST_NUM(tk64->AdjustTime) > MAX_ADJUST_TIME)
					{
						// Remove the second
						ADJUST_TIME *t2 = LIST_DATA(tk64->AdjustTime, 1);

						Delete(tk64->AdjustTime, t2);

						Debug("NUM_ADJUST TIME: %u\n", LIST_NUM(tk64->AdjustTime));

						Free(t2);
					}
				}
				UnlockList(tk64->AdjustTime);
				tk64->Time64 = now;
				tk64->Tick64WithTime64 = tick64;
			}
			first = true;
			n = 0;
		}

		if (tk64->Halt)
		{
			break;
		}

#ifdef	OS_WIN32
		Wait(halt_tick_event, tick_span);
#else	// OS_WIN32
		SleepThread(tick_span);
#endif	// OS_WIN32
	}
}