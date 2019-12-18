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
 int UniGetLineUnix (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int UniGetLineWin32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool UniGetLine(wchar_t *str, UINT size)
{
#ifdef	OS_WIN32
	return UniGetLineWin32(str, size);
#else	// OS_WIN32
	return UniGetLineUnix(str, size);
#endif	// OS_WIN32
}