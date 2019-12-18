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
typedef  int /*<<< orphan*/  ROUTE_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*) ; 
 int /*<<< orphan*/  UnixDeleteRouteEntry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Win32DeleteRouteEntry (int /*<<< orphan*/ *) ; 

void DeleteRouteEntry(ROUTE_ENTRY *e)
{
	Debug("DeleteRouteEntry();\n");
#ifdef	OS_WIN32
	Win32DeleteRouteEntry(e);
#else	// OS_WIN32
	UnixDeleteRouteEntry(e);
#endif
}