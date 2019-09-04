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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */

bool UniGetLineWin32(wchar_t *str, UINT size)
{
	bool ret = false;

#ifdef	OS_WIN32
	ret = Win32InputW(str, size);
#endif	// OS_WIN32

	return ret;
}