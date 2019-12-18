#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT64 ;
struct TYPE_2__ {int /*<<< orphan*/  TickLock; int /*<<< orphan*/  Tick; } ;

/* Variables and functions */
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Win32FastTick64 () ; 
 TYPE_1__* tk64 ; 

UINT64 Tick64()
{
#ifdef	OS_WIN32
	return Win32FastTick64();
#else	// OS_WIN32
	UINT64 tick64;
	if (tk64 == NULL)
	{
		return 0;
	}
	Lock(tk64->TickLock);
	{
		tick64 = tk64->Tick;
	}
	Unlock(tk64->TickLock);
	return tick64;
#endif	// OS_WIN32
}