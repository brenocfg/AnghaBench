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
 int UnixAddRouteEntry (int /*<<< orphan*/ *,int*) ; 
 int Win32AddRouteEntry (int /*<<< orphan*/ *,int*) ; 

bool AddRouteEntryEx(ROUTE_ENTRY *e, bool *already_exists)
{
	bool ret = false;
	Debug("AddRouteEntryEx();\n");
#ifdef	OS_WIN32
	ret = Win32AddRouteEntry(e, already_exists);
#else	// OS_WIN32
	ret = UnixAddRouteEntry(e, already_exists);
#endif
	return ret;
}