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
typedef  int /*<<< orphan*/  SOCK_EVENT ;

/* Variables and functions */
 int /*<<< orphan*/  UnixCleanupSockEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Win32CleanupSockEvent (int /*<<< orphan*/ *) ; 

void CleanupSockEvent(SOCK_EVENT *event)
{
#ifdef	OS_WIN32
	Win32CleanupSockEvent(event);
#else
	UnixCleanupSockEvent(event);
#endif	// OS_WIN32
}