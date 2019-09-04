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

/* Variables and functions */

bool IsIcmpApiSupported()
{
#ifdef	OS_WIN32
	if (w32net->IcmpCloseHandle != NULL &&
		w32net->IcmpCreateFile != NULL &&
		w32net->IcmpSendEcho != NULL)
	{
		return true;
	}
#endif	// OS_WIN32

	return false;
}