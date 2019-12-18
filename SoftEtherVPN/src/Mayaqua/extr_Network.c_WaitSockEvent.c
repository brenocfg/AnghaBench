#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  SOCK_EVENT ;

/* Variables and functions */
 int UnixWaitSockEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int Win32WaitSockEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool WaitSockEvent(SOCK_EVENT *event, UINT timeout)
{
	bool ret = false;
#ifdef	OS_WIN32
	ret = Win32WaitSockEvent(event, timeout);
#else
	ret = UnixWaitSockEvent(event, timeout);
#endif	// OS_WIN32
	return ret;
}