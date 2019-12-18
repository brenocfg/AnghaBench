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
 int GetEnvW_ForUnix (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int GetEnvW_ForWin32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool GetEnvW(wchar_t *name, wchar_t *data, UINT size)
{
#ifdef	OS_WIN32
	return GetEnvW_ForWin32(name, data, size);
#else	// OS_WIN32
	return GetEnvW_ForUnix(name, data, size);
#endif	// OS_WIN32
}